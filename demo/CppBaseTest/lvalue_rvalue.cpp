﻿#include "lvalue_rvalue.hpp"
#include <iostream>
#include <string>
#include <utility>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78619152

namespace lvalue_rvalue_ {
////////////////////////////////////////////////////////////
namespace {
char& get_val(std::string& str, std::string::size_type ix)
{
	return str[ix];
}
}

int test_lvalue_rvalue_1()
{
{
	// 赋值运算符的左侧运算对象必须是一个可修改的左值：
	int i = 0, j = 0, k = 0; // 初始化而非赋值
	const int ci = i; // 初始化而非赋值
	// 下面的赋值语句都是非法的
	//1024 = k; // 错误：字面值是右值
	//i + j = k; // 错误：算术表达式是右值
	//ci = k; // 错误：ci是常量(不可修改的)左值
}

{
	int i = 0;
	int& r = i; // 正确：r引用i
	//int&& rr = i; // 错误：不能将一个右值引用绑定到一个左值上
	//int& r2 = i * 42; // 错误：i*42是一个右值
	const int& r3 = i * 42; // 正确：我们可以将一个const的引用绑定到一个右值上
	int&& rr2 = i * 42; // 正确：将rr2绑定到乘法结果上
}

{
	// 不能将一个右值引用绑定到一个右值引用类型的变量上
	int&& rr1 = 42; // 正确：字面常量是右值
	//int&& rr2 = rr1; // 错误：表达式rr1是左值
	//int rr = &&rr1; // 不能将一个右值引用直接绑定到一个左值上
	int i = 5;
	int&& rr3 = std::move(i); // ok

}

	// 调用一个返回引用的函数得到左值，其它返回类型得到右值
	std::string s{ "a value" };
	std::cout << s << std::endl; // a value
	get_val(s, 0) = 'A';
	std::cout << s << std::endl; // A value

	return 0;
}

/////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/f90831hc.aspx
int test_lvalue_rvalue_2()
{
	int i, j;
	int *p = new int;

	// Correct usage: the variable i is an lvalue.
	i = 7;

	// Incorrect usage: The left operand must be an lvalue (C2106).
	//7 = i; // C2106
	//j * 4 = 7; // C2106

	// Correct usage: the dereferenced pointer is an lvalue.
	*p = i;
	delete p;

	const int ci = 7;
	// Incorrect usage: the variable is a non-modifiable lvalue (C3892).
	//ci = 9; // C3892

	// Correct usage: the conditional operator returns an lvalue.
	((i < 3) ? i : j) = 7;

	return 0;
}

//////////////////////////////////////////////////////////
// reference: http://www.bogotobogo.com/cplusplus/C11/4_C11_Rvalue_Lvalue.php
namespace {
	class cat {};

	int square(int x) { return x*x; }
	int square2(int& x) { return x*x; }
}

int test_lvalue_rvalue_3()
{
{ // lvalue examples
	int i = 7;  // i: lvalue
	int *pi = &i;  // i is addressable
	i = 10;  // we can modify it

	class cat {};
	cat c;   // c is an lvalue for a user defined type
}

{ // rvalue examples
	int i = 7;  // i: lvalue but 7 is rvalue
	int k = i + 3;  // (i+3) is an rvalue
	//int *pi = &(i + 3); // error, it's not addressable
	//i + 3 = 10;   // error - cannot assign a value to it
	//3 = i;        // error - not assignable

	cat c;
	c = cat();   // cat() is an rvalue

}

{
	int sq = square(10);  // square(10) is an rvalue
}

{
	int i = 7;
	square(i);  // OK
	square(7);
	//square2(7);  // error, 7 is an rvalue and cannot be assigned to a reference
}

{
	int a = 7; // a is lvalue & 7 is rvalue
	int b = (a + 2); // b is lvalue & (a+2) is rvalue
	int c = (a + b); // c is lvalue & (a+b) is rvalue
	int * ptr = &a; // Possible to take address of lvalue
	//int * ptr3 = &(a + 1);  // Compile Error. Can not take address of rvalue
}

	return 0;
}

//////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/reference
namespace {
void double_string(std::string& s)
{
	s += s; // 's' is the same object as main()'s 'str'
}

char& char_number(std::string& s, std::size_t n)
{
	return s.at(n); // string::at() returns a reference to char
}
}

int test_lvalue_rvalue_4()
{
	// 1. Lvalue references can be used to alias an existing object (optionally with different cv-qualification):
	std::string s = "Ex";
	std::string& r1 = s;
	const std::string& r2 = s;

	r1 += "ample";           // modifies s
	//  r2 += "!";               // error: cannot modify through reference to const
	std::cout << r2 << '\n'; // prints s, which now holds "Example"

	// 2. They can also be used to implement pass-by-reference semantics in function calls:
	std::string str = "Test";
	double_string(str);
	std::cout << str << '\n';

	// 3. When a function's return type is lvalue reference, the function call expression becomes an lvalue expression
	std::string str_ = "Test";
	char_number(str_, 1) = 'a'; // the function call is lvalue, can be assigned to
	std::cout << str_ << '\n';

	return 0;
}

/////////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/language/reference
namespace {
void f(int& x)
{
	std::cout << "lvalue reference overload f(" << x << ")\n";
}

void f(const int& x)
{
	std::cout << "lvalue reference to const overload f(" << x << ")\n";
}

void f(int&& x)
{
	std::cout << "rvalue reference overload f(" << x << ")\n";
}
}

int test_lvalue_rvalue_5()
{
	// 1. Rvalue references can be used to extend the lifetimes of temporary objects
	// (note, lvalue references to const can extend the lifetimes of temporary objects too, but they are not modifiable through them):
	std::string s1 = "Test";
	//  std::string&& r1 = s1;           // error: can't bind to lvalue

	const std::string& r2 = s1 + s1; // okay: lvalue reference to const extends lifetime
	//  r2 += "Test";                    // error: can't modify through reference to const

	std::string&& r3 = s1 + s1;      // okay: rvalue reference extends lifetime
	r3 += "Test";                    // okay: can modify through reference to non-const
	std::cout << r3 << '\n';

	// 2. More importantly, when a function has both rvalue reference and lvalue reference overloads,
	// the rvalue reference overload binds to rvalues (including both prvalues and xvalues),
	// while the lvalue reference overload binds to lvalues:
	int i = 1;
	const int ci = 2;
	f(i);  // calls f(int&)
	f(ci); // calls f(const int&)
	f(3);  // calls f(int&&)
	// would call f(const int&) if f(int&&) overload wasn't provided
	f(std::move(i)); // calls f(int&&)

	// This allows move constructors, move assignment operators, and other move-aware functions
	// (e.g. vector::push_back() to be automatically selected when suitable.

	return 0;
}

/////////////////////////////////////////////////////////////
// reference: http://www.bogotobogo.com/cplusplus/C11/5_C11_Move_Semantics_Rvalue_Reference.php
namespace {
void printReference(int& value)
{
	std::cout << "lvalue: value = " << value << std::endl;
}

void printReference(int&& value)
{
	std::cout << "rvalue: value = " << value << std::endl;
}

int getValue()
{
	int temp_ii = 99;
	return temp_ii;
}
}

int test_lvalue_rvalue_6()
{
	int ii = 11;
	printReference(ii);
	printReference(getValue());  //  printReference(99);

	return 0;
}

////////////////////////////////////////////////////////////
// reference: https://msdn.microsoft.com/en-us/library/dd293668.aspx
namespace {
template<typename T> struct S;

// The following structures specialize S by 
// lvalue reference (T&), const lvalue reference (const T&), 
// rvalue reference (T&&), and const rvalue reference (const T&&).
// Each structure provides a print method that prints the type of 
// the structure and its parameter.
template<typename T> struct S<T&> {
	static void print(T& t)
	{
		std::cout << "print<T&>: " << t << std::endl;
	}
};

template<typename T> struct S<const T&> {
	static void print(const T& t)
	{
		std::cout << "print<const T&>: " << t << std::endl;
	}
};

template<typename T> struct S<T&&> {
	static void print(T&& t)
	{
		std::cout << "print<T&&>: " << t << std::endl;
	}
};

template<typename T> struct S<const T&&> {
	static void print(const T&& t)
	{
		std::cout << "print<const T&&>: " << t << std::endl;
	}
};

// This function forwards its parameter to a specialized
// version of the S type.
template <typename T> void print_type_and_value(T&& t)
{
	S<T&&>::print(std::forward<T>(t));
}

// This function returns the constant string "fourth".
const std::string fourth() { return std::string("fourth"); }
}

int test_lvalue_rvalue_7()
{
	// The following call resolves to:
	// print_type_and_value<string&>(string& && t)
	// Which collapses to:
	// print_type_and_value<string&>(string& t)
	std::string s1("first");
	print_type_and_value(s1);

	// The following call resolves to:
	// print_type_and_value<const string&>(const string& && t)
	// Which collapses to:
	// print_type_and_value<const string&>(const string& t)
	const std::string s2("second");
	print_type_and_value(s2);

	// The following call resolves to:
	// print_type_and_value<string&&>(string&& t)
	print_type_and_value(std::string("third"));

	// The following call resolves to:
	// print_type_and_value<const string&&>(const string&& t)
	print_type_and_value(fourth());

	return 0;
}

} // namespace lvalue_rvalue_

