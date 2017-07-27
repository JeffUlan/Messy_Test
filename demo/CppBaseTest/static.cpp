#include "static.hpp"
#include <iostream>

///////////////////////////////////////////////////////////
size_t count_calls()
{
	// �ֲ���̬����(local static object)�ڳ����ִ��·����һ�ξ���������
	// ���ʱ��ʼ��,����ֱ��������ֹ�ű����٣��ڴ��ڼ伴ʹ�������ڵĺ�����
	// ��ִ��Ҳ���������Ӱ�졣
	static size_t ctr = 0; // ���ý��������ֵ��Ȼ��Ч
	return ++ctr;
}

int test_static_1()
{
	for (int i = 0; i < 10; ++i) {
		std::cout << count_calls() << std::endl;
	}

	return 0;
}

