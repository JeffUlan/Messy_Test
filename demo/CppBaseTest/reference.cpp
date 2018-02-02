#include "reference.hpp"
#include <iostream>
#include <utility> // std::move

// Blog: http://blog.csdn.net/fengbingchun/article/details/69820184

int test_reference_1()
{
	// 1. ��ͨ������
	int ival = 1024;
	int &refVal = ival; // refValָ��ival(��ival����һ������)
	//int &refVal2; // error�����ñ��뱻��ʼ��
	int &refVal3 = refVal; // refVal3�󶨵����Ǹ���refVal�󶨵Ķ����ϣ�������ǰ󶨵�ival��
	// ������refVal�󶨵Ķ����ֵ��ʼ������i
	int i = refVal; // correct��i����ʼ��Ϊival��ֵ
	// ������һ������ж��������ã�����ÿ�����ñ�ʶ���������Է���&��ͷ
	int i1 = 1024, i2 = 2048;
	int &r = i1, r2 = i2;
	int i3 = 1024, &ri = i3;
	int &r3 = i3, &r4 = i2; // r3��r4��������
	//int &refVal4 = 10; // error: �������͵ĳ�ʼֵ������һ������
	double dval = 3.14;
	//int &refVal5 = dval; // error: �˴��������͵ĳ�ʼֵ������int�Ͷ���
	const int &refVal6 = dval; // correct
	// �������������������������ʽ��
	//const int temp = dval; // ��˫���ȸ���������һ����ʱ�����ͳ���
	//const int &refVal6 = temp; // ��refVal6�������ʱ��

	// 2. const������
	// �Գ��������ò��ܱ������޸������󶨵Ķ���
	const int ci = 1024;
	const int &r1 = ci; // correct: ���ü����Ӧ�Ķ����ǳ���
	//r1 = 42; // error: r1�ǶԳ���������
	//int &r2 = ci; // error: ��ͼ��һ���ǳ�������ָ��һ����������

	int i4 = 42;
	const int &r6 = i4; // ����const int&�󶨵�һ����ͨint������
	const int &r7 = 42; // correct: r7��һ����������
	const int &r8 = r6 * 2; // correct: r8��һ����������
	//int &r9 = r6 * 2; // error: r9��һ����ͨ�ķǳ�������

	// ���������ý������ÿɲ���Ĳ����������޶����������õĶ������ǲ���һ������δ���޶�
	int x = 42;
	int &rx = x; // ����rx�󶨶���x
	const int &ry = x; // ryҲ�󶨶���x,���ǲ�����ͨ��ry�޸�x��ֵ
	rx = 0; // rx���ǳ�����x��ֵ�޸�Ϊ0
	//ry = 0; // error: ry��һ����������

	return 0;
}

// �ú�������һ��int��������ã�Ȼ�󽫶����ֵ��Ϊ0
static void reset(int &i) // i�Ǵ���reset�����Ķ������һ������
{
	i = 0; // �ı���i�����ö����ֵ
}

int test_reference_2()
{
	int j = 42;
	reset(j); // j�������÷�ʽ������ֵ���ı�
	fprintf(stderr, "j = %d\n", j); // j = 0

	return 0;
}

int test_reference_3()
{
	int i = 42;
	int &r = i; // correct: r����i
	//int &&rr = i; // error: ���ܽ�һ����ֵ���ð󶨵�һ����ֵ��
	//int &r2 = i * 42; // error: i*42��һ����ֵ
	const int &r3 = i * 42; // correct: ���Խ�һ��const�����ð󶨵�һ����ֵ��
	int &&rr2 = i * 42; // correct: ��rr2�󶨵��˷������

	int &&rr1 = 42; // correct: ���泣������ֵ
	//int &&rr3 = rr1; // error: ���ʽrr1����ֵ
	int &&rr4 = std::move(rr1); // correct

	return 0;
}

