#include <iostream>
#include "common.hpp"

int main()
{
	int ret = test_process_programming_1();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
