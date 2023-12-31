﻿#include "decltype.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <iomanip>
#include <typeinfo>

// Blog: https://blog.csdn.net/fengbingchun/article/details/131264728

namespace {

decltype(auto) increase(int& a) { a++; return a; }

int xxx = 123;
auto f(const int& i) { return i; } // return type is "int"
static_assert(std::is_same<const int&, decltype(f(xxx))>::value == 0);
static_assert(std::is_same<int, decltype(f(xxx))>::value == 1);

decltype(auto) g(const int& i) { return i; } // return type is "const int&"
static_assert(std::is_same<const int&, decltype(g(xxx))>::value == 1);

int xx = 1;
decltype(auto) f2() { return xx; }  // return type is int, same as decltype(x)
static_assert(std::is_same<int, decltype(f2())>::value == 1);
decltype(auto) f3() { return(xx); } // return type is int&, same as decltype((x))
static_assert(std::is_same<int&, decltype(f3())>::value == 1);
//const decltype(auto)& f4(const int) { return xx; } // "const decltype(auto)&" is an error, decltype(auto) must be used on its own
												     // error:“decltype(auto)”不能与任何其他类型说明符组合

//auto f5(bool flag) {
//	if (flag) return 1;
//	else return 1.0; // error: 所有返回表达式必须推导为相同类型: 以前为“int”
//}

//class AA {
//	virtual auto g() { return 1; } // error: 虚成员函数不应具有含“auto”的返回类型
//};

} // namespace

int test_decltype_14_1()
{
	int a = 4;
	auto& v2 = increase(a);
	std::cout << "v2:" << v2 << "\n"; // v2:5
	v2 = 10;
	std::cout << "a:" << a << "\n"; // a:10

	return 0;
}

int test_decltype_14_2()
{
	const int x = 0;
	//x = 2; // error C3892: “x”: 不能给常量赋值
	auto x1 = x; // int
	x1 = 2;
	decltype(auto) x2 = x; // const int
	//x2 = 3; // error C3892: “x2”: 不能给常量赋值

	int y = 2;
	int& y1 = y;
	auto y2 = y1; // int
	y2 = 5;
	std::cout << "y:" << y << "\n"; // y:2
	decltype(auto) y3 = y1; // int&
	y3 = 10;
	std::cout << "y:" << y << "\n"; // y:10

	int&& z = 2;
	auto z1 = std::move(z); // int
	z1 = 5;
	std::cout << "z:" << z << "\n"; // z:2
	decltype(auto) z2 = std::move(z); // int&&
	z2 = 10;
	std::cout << "z:" << z << "\n"; // z:10

	return 0;
}


// Blog: http://blog.csdn.net/fengbingchun/article/details/52504519

//////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/decltype
struct A { double x; };
const A* a = new A{ 0 };

decltype(a->x) y;       // type of y is double (declared type)
decltype((a->x)) z = y; // type of z is const double& (lvalue expression)

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u); // return type depends on template parameters

int test_decltype1()
{
	int i = 33;
	decltype(i) j = i * 2;

	std::cout << "i = " << i << ", " << "j = " << j << '\n';

	auto f = [](int a, int b) -> int
	{
		return a * b;
	};

	decltype(f) g = f; // the type of a lambda function is unique and unnamed
	i = f(2, 2);
	j = g(3, 3);

	std::cout << "i = " << i << ", " << "j = " << j << '\n';

	return 0;
}

///////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/zh-cn/library/dd537655.aspx
template<typename T1, typename T2>
auto Plus(T1&& t1, T2&& t2) ->
decltype(std::forward<T1>(t1) +std::forward<T2>(t2))
{
	return std::forward<T1>(t1) +std::forward<T2>(t2);
}

class X
{
	friend X operator+(const X& x1, const X& x2)
	{
		return X(x1.m_data + x2.m_data);
	}

public:
	X(int data) : m_data(data) {}
	int Dump() const { return m_data; }
private:
	int m_data;
};

int test_decltype2()
{
	// Integer 
	int i = 4;
	std::cout << "Plus(i, 9) = " << Plus(i, 9) << std::endl;

	// Floating point
	float dx = 4.0;
	float dy = 9.5;
	std::cout << std::setprecision(3) << "Plus(dx, dy) = " << Plus(dx, dy) << std::endl;

	// String
	std::string hello = "Hello, ";
	std::string world = "world!";
	std::cout << Plus(hello, world) << std::endl;

	// Custom type
	X x1(20);
	X x2(22);
	X x3 = Plus(x1, x2);
	std::cout << "x3.Dump() = " << x3.Dump() << std::endl;

	return 0;
}

///////////////////////////////////////////////////
// reference: http://thbecker.net/articles/auto_and_decltype/section_06.html
struct S {
	S(){ m_x = 42; }
	int m_x;
};

int x;
const int cx = 42;
const int& crx = x;
const S* p = new S();

// x is declared as an int: x_type is int.
typedef decltype(x) x_type;

// auto also deduces the type as int: a_ is an int.
auto a_ = x;

// cx is declared as const int: cx_type is const int.
typedef decltype(cx) cx_type;

// auto drops the const qualifier: b is int.
auto b = cx;

// crx is declared as const int&: crx_type is const int&.
typedef decltype(crx) crx_type;

// auto drops the reference and the const qualifier: c is an int.
auto c = crx;

// S::m_x is declared as int: m_x_type is int
// Note that p->m_x cannot be assigned to. It is effectively
// constant because p is a pointer to const. But decltype goes
// by the declared type, which is int.
typedef decltype(p->m_x) m_x_type;

// auto sees that p->m_x is const, but it drops the const
// qualifier. Therefore, d is an int.
auto d = p->m_x;
