#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "funset.hpp"

TEST(add_test, sum)
{
	EXPECT_EQ(add(1, 2), 3);
	EXPECT_EQ(add(-1, 2), 3) << "this is a error!"; // ����ͨ����������<<����һЩ�Զ������Ϣ���
	EXPECT_EQ(add(2, 3), 5);
	ASSERT_NE(add(3, 4), 1);
	fprintf(stderr, "EXPECT_*�汾�Ķ���ʧ��ʱ����������ʧ�ܣ���������ֹ��ǰ����\n");
	ASSERT_EQ(add(3, 4), 2);
	fprintf(stderr, "ASSERT_*�汾�Ķ���ʧ��ʱ���������ʧ�ܣ���������ǰ��������ǰ������ASSERT_*�������佫����ִ��\n");
}

// ��ʱ���ò���, ֻ�����߼���������Ԫ������ǰ����� DISABLE_ ǰ׺�����Ͳ���ִ����
TEST(DISABLE_add_test, no_run_test) // TEST(add_test, DISABLE_no_run_test)
{
	EXPECT_EQ(add(1, 2), 3);
}
