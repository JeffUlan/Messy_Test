#include <iostream>
#include "common.hpp"

int main()
{
	int ret = test_priority_queue_4();

	if (ret == 0) fprintf(stderr, "test success\n");
	else fprintf(stderr, "test fail\n");

	return 0;
}
