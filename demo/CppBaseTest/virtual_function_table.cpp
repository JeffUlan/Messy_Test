#include "virtual_function_table.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/79592347

namespace virtual_function_table_ {

// reference: http://www.learncpp.com/cpp-tutorial/125-the-virtual-table/
class Base {
public:
	Base() { fprintf(stdout, "Base::Base\n"); }
	virtual void function1() { fprintf(stdout, "Base::function1\n"); }
	virtual void function2() { fprintf(stdout, "Base::function2\n"); }
	void f1() { fprintf(stdout, "Base::f1\n"); }
	~Base() { fprintf(stdout, "Base::~Base\n"); }
};

class D1 : public Base {
public:
	D1() { fprintf(stdout, "D1::D1\n"); }
	virtual void function1() override { fprintf(stdout, "D1::function1\n"); }
	virtual void function3() { fprintf(stdout, "D1::function3\n"); }
	void f2() { fprintf(stdout, "D1::f2\n"); }
	~D1() { fprintf(stdout, "D1::~D1\n"); }
};

class D2 : public Base {
public:
	D2() { fprintf(stdout, "D2::D2\n"); }
	virtual void function2() override { fprintf(stdout, "D2::function2\n"); }
	void f3() { fprintf(stdout, "D2::f3\n"); }
	~D2() { fprintf(stdout, "D2::~D2\n"); }
};

class D3 {
public:
	D3() { fprintf(stdout, "D3::D3\n"); }
	void f4() { fprintf(stdout, "D3::f4\n"); }
	~D3() { fprintf(stdout, "D3::~D3\n"); }
};

int test_virtual_function_table_1()
{
	D1* p1 = new D1();
	fprintf(stdout, "p1 address: %p\n", (void*)p1);
	Base* b = static_cast<D1*>(p1);
	fprintf(stdout, "b address: %p\n", (void*)b);
	b->function1();
	b->function2();
	// �κ���ͼʹ�ø���ָ������������е�δ���Ǹ���ĳ�Ա��������Ϊ���ᱻ��������Ϊ�Ƿ�
	//b->function3(); // Error: class "virtual _function_table_::Base" û�г�Ա "function3"
	delete p1;
	fprintf(stdout, "\n");

	Base* p2 = new D1();
	fprintf(stdout, "p2 address: %p\n", (void*)p2);
	p2->function1();
	p2->function2();
	delete dynamic_cast<D1*>(p2);
	fprintf(stdout, "\n");

	D1 d1 = D1();
	fprintf(stdout, "d1 address: %p\n", (void*)&d1);
	d1.function1();
	d1.function2();
	fprintf(stdout, "\n");

	D2 d2 = D2();
	fprintf(stdout, "d2 address: %p\n", (void*)&d2);
	Base* b2 = &d2;
	fprintf(stdout, "b2 address: %p\n", (void*)b2);
	b2->function1();
	b2->function2();
	fprintf(stdout, "\n");

	D3 d3 = D3();
	fprintf(stdout, "\n");

	return 0;
}

} // namespace virtual_function_table_

