/* ******************************************************************************
 * Copyright (c) 2015 Google, Inc.  All rights reserved.
 * ******************************************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of VMware, Inc. nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL VMWARE, INC. OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/* Code Manipulation API Sample:
 * opcodes.c
 *
 * Reports the dynamic count of the total number of instructions executed
 * broken down by opcode.
 */

#include "dr_api.h"
#include "drx.h"
#include <stdlib.h> /* qsort */

#ifdef WINDOWS
# define DISPLAY_STRING(msg) dr_messagebox(msg)
#else
# define DISPLAY_STRING(msg) dr_printf("%s\n", msg);
#endif

#define NULL_TERMINATE(buf) buf[(sizeof(buf)/sizeof(buf[0])) - 1] = '\0'

/* We keep a separate execution count per opcode.
 *
 * XXX: our counters are racy on ARM.  We use DRX_COUNTER_LOCK to make them atomic
 * (at a perf cost) on x86.
 *
 * XXX: we're using 32-bit counters.  64-bit counters are more challenging: they're
 * harder to make atomic on 32-bit x86, and drx does not yet support them on ARM.
 */
enum {
#ifdef X86
    ISA_X86_32,
    ISA_X86_64,
#elif defined(ARM)
    ISA_ARM_A32,
    ISA_ARM_THUMB,
#endif
    NUM_ISA_MODE,
};
static uint count[NUM_ISA_MODE][OP_LAST+1];
#define NUM_COUNT sizeof(count[0])/sizeof(count[0][0])
/* We only display the top 15 counts.  This sample could be extended to
 * write all the counts to a file.
 *
 * XXX: DynamoRIO uses a separate stack for better transparency. DynamoRIO stack
 * has limited size, so we should keep NUM_COUNT_SHOW small to avoid the message
 * buffer (char msg[NUM_COUNT_SHOW*80]) in event_exit() overflowing the stack.
 * It won't work on Windows either if the output is too large.
 */
#define NUM_COUNT_SHOW 15

static void event_exit(void);
static dr_emit_flags_t event_basic_block(void *drcontext, void *tag, instrlist_t *bb,
                                         bool for_trace, bool translating);

DR_EXPORT void
dr_client_main(client_id_t id, int argc, const char *argv[])
{
    dr_set_client_name("DynamoRIO Sample Client 'opcodes'",
                       "http://dynamorio.org/issues");
    /* register events */
    dr_register_exit_event(event_exit);
    dr_register_bb_event(event_basic_block);

    /* make it easy to tell, by looking at log file, which client executed */
    dr_log(NULL, LOG_ALL, 1, "Client 'opcodes' initializing\n");
#ifdef SHOW_RESULTS
    /* also give notification to stderr */
    if (dr_is_notify_on()) {
# ifdef WINDOWS
        /* ask for best-effort printing to cmd window.  must be called at init. */
        dr_enable_console_printing();
# endif
        dr_fprintf(STDERR, "Client opcodes is running\n");
    }
#endif
}

#ifdef SHOW_RESULTS
/* We use cur_isa to iterate each ISA counters in event_exit, so there will be
 * no race on accessing it in compare_counts.
 */
static uint cur_isa;
static int
compare_counts(const void *a_in, const void *b_in)
{
    const uint a = *(const uint *)a_in;
    const uint b = *(const uint *)b_in;
    if (count[cur_isa][a] > count[cur_isa][b])
        return 1;
    if (count[cur_isa][a] < count[cur_isa][b])
        return -1;
    return 0;
}

static const char *
get_isa_mode_name(uint isa_mode)
{
#ifdef X86
    return (isa_mode == ISA_X86_32) ? "32-bit X86" : "64-bit AMD64";
#elif defined(ARM)
    return (isa_mode == ISA_ARM_A32) ? "32-bit ARM" : "32-bit Thumb";
#else
    return "unknown";
#endif
}
#endif

static void
event_exit(void)
{
#ifdef SHOW_RESULTS
    char msg[NUM_COUNT_SHOW*80];
    int len, i;
    size_t sofar = 0;
    /* First, sort the counts */
    uint indices[NUM_COUNT];
    for (cur_isa = 0; cur_isa < NUM_ISA_MODE; cur_isa++) {
        sofar = 0;
        for (i = 0; i <= OP_LAST; i++)
            indices[i] = i;
        qsort(indices, NUM_COUNT, sizeof(indices[0]), compare_counts);

        if (count[cur_isa][indices[OP_LAST]] == 0)
            continue;
        len = dr_snprintf(msg, sizeof(msg)/sizeof(msg[0]),
                          "Top %d opcode execution counts in %s mode:\n",
                          NUM_COUNT_SHOW, get_isa_mode_name(cur_isa));
        DR_ASSERT(len > 0);
        sofar += len;
        for (i = OP_LAST - 1 - NUM_COUNT_SHOW; i <= OP_LAST; i++) {
            if (count[cur_isa][indices[i]] != 0) {
                len = dr_snprintf(msg + sofar, sizeof(msg)/sizeof(msg[0]) - sofar,
                                  "  %9lu : %-15s\n", count[cur_isa][indices[i]],
                                  decode_opcode_name(indices[i]));
                DR_ASSERT(len > 0);
                sofar += len;
            }
        }
        NULL_TERMINATE(msg);
        DISPLAY_STRING(msg);
    }
#endif /* SHOW_RESULTS */
}

static uint
get_count_isa_idx(void *drcontext)
{
    switch (dr_get_isa_mode(drcontext)) {
#ifdef X86
    case DR_ISA_X86:
        return ISA_X86_32;
    case DR_ISA_AMD64:
        return ISA_X86_64;
#elif defined(ARM)
    case DR_ISA_ARM_A32:
        return ISA_ARM_A32;
        break;
    case DR_ISA_ARM_THUMB:
        return ISA_ARM_THUMB;
#endif
    default:
        DR_ASSERT(false); /* NYI */
    }
    return 0;
}

static dr_emit_flags_t
event_basic_block(void *drcontext, void *tag, instrlist_t *bb,
                  bool for_trace, bool translating)
{
    instr_t *instr;
    instr_t *first = instrlist_first_app(bb);
    uint isa_idx = get_count_isa_idx(drcontext);

#ifdef VERBOSE
    dr_printf("in dynamorio_basic_block(tag="PFX")\n", tag);
# ifdef VERBOSE_VERBOSE
    instrlist_disassemble(drcontext, tag, bb, STDOUT);
# endif
#endif

    for (instr = instrlist_first_app(bb);
         instr != NULL;
         instr = instr_get_next_app(instr)) {
        /* We insert all increments sequentially up front so that drx can
         * optimize the spills and restores.
         */
        drx_insert_counter_update(drcontext, bb, first,
                                  SPILL_SLOT_1, IF_ARM_(SPILL_SLOT_2)
                                  &count[isa_idx][instr_get_opcode(instr)], 1,
                                  /* DRX_COUNTER_LOCK is not yet supported on ARM */
                                  IF_X86_ELSE(DRX_COUNTER_LOCK, 0));
    }

#if defined(VERBOSE) && defined(VERBOSE_VERBOSE)
    dr_printf("Finished instrumenting dynamorio_basic_block(tag="PFX")\n", tag);
    instrlist_disassemble(drcontext, tag, bb, STDOUT);
#endif
    return DR_EMIT_DEFAULT;
}
