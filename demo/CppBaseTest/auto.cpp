#include "auto.hpp"
#include <iostream>
#include <cmath>
#include <typeinfo>
#include <string>
#include <map>
#include <list>
#include <deque>
#include <vector>

// Blog: http://blog.csdn.net/fengbingchun/article/details/51834927

//////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/auto
template<class T, class U>
auto add(T t, U u) -> decltype(t + u) // the return type is the type of operator+(T, U)
{
	return t + u;
}

auto get_fun(int arg) -> double(*)(double) // same as: double (*get_fun(int))(double)
{
	switch (arg) {
		case 1: return std::fabs;
		case 2: return std::sin;
		default: return std::cos;
	}
}

int test_auto1()
{
	auto a = 1 + 2;
	std::cout << "type of a: " << typeid(a).name() << '\n'; // type of a: int
	auto b = add(1, 1.2);
	std::cout << "type of b: " << typeid(b).name() << '\n'; // type of b: double
	auto c = { 1, 2 };
	std::cout << "type of c: " << typeid(c).name() << '\n'; // type of c: class std::initializer_list<int>

	auto my_lambda = [](int x) { return x + 3; };
	std::cout << "my_lambda: " << my_lambda(5) << '\n'; // my_lambda: 8

	auto my_fun = get_fun(2);
	std::cout << "type of my_fun: " << typeid(my_fun).name() << '\n'; // type of my_fun: double (__cdecl*)(double)
	std::cout << "my_fun: " << my_fun(3) << '\n'; // my_fun: 0.14112

	// auto int x; // error as of C++11: "auto" is no longer a storage-class specifier // error C3530: ��auto���������κ���������˵�������

	return 0;
}

////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dd293667(v=vs.120).aspx
int f(int x) { return x; }

int test_auto2()
{
	int count = 10;
	int& countRef = count;
	auto myAuto = countRef;

	countRef = 11;
	std::cout << count << " " << std::endl; // 11

	myAuto = 12;
	std::cout << count << std::endl; // 11

	// 1. �����������Ч�� �ڵ�һ������У����� j ����Ϊ���� int�� �ڵڶ�����䣬��Ϊ��ʼ�����ʽ (0) �����������Ա��� k �Ƶ�Ϊ int ����
	int j = 0;  // Variable j is explicitly type int.
	auto k = 0; // Variable k is implicitly type int because 0 is an integer.

	// 2. ����������Ч�����ڶ��������ȵ�һ����
	std::map<int, std::list<std::string>> m;
	std::map<int, std::list<std::string>>::iterator i = m.begin();
	auto i_ = m.begin();

	// 3. ���� iter �� elem ��������
	std::deque<double> dqDoubleData(10, 0.1);

	for (auto iter = dqDoubleData.begin(); iter != dqDoubleData.end(); ++iter) { /* ... */}

	// prefer range-for loops with the following information in mind
	// (this applies to any range-for with auto, not just deque)

	for (auto elem : dqDoubleData) // COPIES elements, not much better than the previous examples 
	{ /* ... */ }

	for (auto& elem : dqDoubleData) // observes and/or modifies elements IN-PLACE
	{ /* ... */ }

	for (const auto& elem : dqDoubleData) // observes elements IN-PLACE
	{ /* ... */ }

	// 4. ʹ�� new �����
	double x = 12.34;
	auto *y = new auto(x), **z = new auto(&x);

	// 5. ���з��Ž���Ϊͬһ����
	auto x_ = 1, *y_ = &x_, **z_ = &y_; // Resolves to int.
	auto a(2.01), *b(&a);         // Resolves to double.
	auto c = 'a', *d(&c);          // Resolves to char.
	auto m_ = 1, &n_ = m_;            // Resolves to int.

	// 6. ʹ����������� (?:)
	int v1 = 100, v2 = 200;
	auto e = v1 > v2 ? v1 : v2;

	// 7. ������ x7 ��ʼ������ int�������õı��� y7 ��ʼ��Ϊ���� const int���������� fp ��ʼ��Ϊָ�򷵻����� int �ĺ�����ָ��
	auto x7 = f(0);
	const auto & y7 = f(1);
	int(*p)(int x7);
	p = f;
	auto fp = p;

	return 0;
}

/////////////////////////////////////
// reference: http://www.learncpp.com/cpp-tutorial/4-8-the-auto-keyword/
int add_3(int x, int y)
{
	return x + y;
}

int test_auto3()
{
	auto d = 5.0; // 5.0 is a double literal, so d will be type double
	auto i = 1 + 2; // 1 + 2 evaluates to an integer, so i will be type int

	auto sum = add_3(5, 6); // add_3() returns an int, so sum will be type int

	return 0;
}
