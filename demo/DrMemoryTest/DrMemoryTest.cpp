#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/51626705

void test1(); // �ڴ�й¶
void test2(); // �Ƿ�����
void test3(); // δ��ʼ����
void test4(); // Heap ������������(Invalid Heap Argument)

int main()
{
	// reference: http://www.ibm.com/developerworks/cn/linux/1309_liuming_drmemory/
	test4();

	std::cout << "ok" << std::endl;
	return 0;
}

void test1()
{
	char *ptr;
	for (int i = 0; i<100; i++) {
		ptr = (char*)malloc(i);

		if (i % 2) free(ptr);
	}
}

void test2()
{
	char *x = (char*)malloc(8);
	char c = *(x + 8); // buffer overlow
	free(x);
	c = *x; // read free memory
}

typedef struct T_ {
	char a;
	char b;
}T;

void test3()
{
	T a, b;
	char x;
	a.a = 'a';
	a.b = 'b';
	b.a = x; // error C4700:ʹ����δ��ʼ���ľֲ�����x,��ʹvs2013�ܹ��������룬�轫���������е�C/C++ SDL���ر�
	if (b.a == 10)
		memcpy(&b, &a, sizeof(T));
}

void test4()
{
	char * ptr = NULL;
	ptr = new char;
	free(ptr);
	free(ptr); //
}

