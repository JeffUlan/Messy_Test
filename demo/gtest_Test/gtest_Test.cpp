#include <iostream>
#include <vector>
#include <gtest/gtest.h>

int main()
{
	std::vector<char*> argv{
#ifdef _DEBUG
		"E:/GitCode/Messy_Test/lib/dbg/x64_vc12/gtest_Test.exe",
#else
		"E:/GitCode/Messy_Test/lib/rel/x64_vc12/gtest_Test.exe",
#endif
		"--gtest_repeat=2", // �ظ����в���
		//"--gtest_break_on_failure", // ����failure�˳�
		"--gtest_filter=*", // ָ����Ҫ���е�tests
		//"--gtest_print_time=0", // don't print the elapsed time of each test
		"--gtest_output=xml:E:/GitCode/Messy_Test/testdata/info.xml" // ��������ָ����xml�ļ�
	};
	int argc = argv.size();

	// Initializes Google Test.  This must be called before calling RUN_ALL_TESTS()
	// ��ʼ�������������в���
	testing::InitGoogleTest(&argc, argv.data());

	// Use this function in main() to run all tests.  It returns 0 if all
	// tests are successful, or 1 otherwise
	int ret = RUN_ALL_TESTS();
	if (ret == 0) fprintf(stderr, "========== all tests are succeseful =========\n");
	else fprintf(stderr, "********** some tests are failed **********\n");

	return 0;
}
