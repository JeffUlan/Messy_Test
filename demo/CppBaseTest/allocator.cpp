#include "allocator.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78943527

namespace allocator_ {

////////////////////////////////////////////////
// reference: C++ Primer(Fifth Edition) 12.2.2
int test_allocator_1()
{
	std::allocator<std::string> alloc; // ���Է���string��allocator����
	int n{ 5 };
	auto const p = alloc.allocate(n); // ����n��δ��ʼ����string

	auto q = p; // qָ��������Ԫ��֮���λ��
	alloc.construct(q++); // *qΪ���ַ���
	alloc.construct(q++, 10, 'c'); // *qΪcccccccccc
	alloc.construct(q++, "hi"); // *qΪhi

	std::cout << *p << std::endl; // ��ȷ��ʹ��string����������
	//std::cout << *q << std::endl; // ���ѣ�qָ��δ������ڴ�
	std::cout << p[0] << std::endl;
	std::cout << p[1] << std::endl;
	std::cout << p[2] << std::endl;

	while (q != p) {
		alloc.destroy(--q); // �ͷ��������������string
	}

	alloc.deallocate(p, n);

	return 0;
}

int test_allocator_2()
{
	std::vector<int> vi{ 1, 2, 3, 4, 5 };

	// �����vi��Ԫ����ռ�ÿռ��һ���Ķ�̬�ڴ�
	std::allocator<int> alloc;
	auto p = alloc.allocate(vi.size() * 2);
	// ͨ������vi�е�Ԫ���������p��ʼ��Ԫ��
	/* ���ƿ����㷨��uninitialized_copy��������������������ǰ������ʾ�������У���������ʾ
	��ЩԪ�ؽ�Ҫ��������Ŀ�Ŀռ䡣���ݸ�uninitialized_copy��Ŀ��λ�õ���������ָ��δ�����
	�ڴ档��copy��ͬ��uninitialized_copy�ڸ���Ŀ��λ�ù���Ԫ�ء�
	����copy��uninitialized_copy����(�������)Ŀ��λ�õ���������ˣ�һ��uninitialized_copy����
	�᷵��һ��ָ�룬ָ�����һ�������Ԫ��֮���λ�á�
	*/
	auto q = std::uninitialized_copy(vi.begin(), vi.end(), p);
	// ��ʣ��Ԫ�س�ʼ��Ϊ42
	std::uninitialized_fill_n(q, vi.size(), 42);

	return 0;
}

////////////////////////////////////////////////////////////
// reference: http://www.modernescpp.com/index.php/memory-management-with-std-allocator
int test_allocator_3()
{
	std::cout << std::endl;

	std::allocator<int> intAlloc;

	std::cout << "intAlloc.max_size(): " << intAlloc.max_size() << std::endl;
	int* intArray = intAlloc.allocate(100);

	std::cout << "intArray[4]: " << intArray[4] << std::endl;

	intArray[4] = 2011;

	std::cout << "intArray[4]: " << intArray[4] << std::endl;

	intAlloc.deallocate(intArray, 100);

	std::cout << std::endl;

	std::allocator<double> doubleAlloc;
	std::cout << "doubleAlloc.max_size(): " << doubleAlloc.max_size() << std::endl;

	std::cout << std::endl;

	std::allocator<std::string> stringAlloc;
	std::cout << "stringAlloc.max_size(): " << stringAlloc.max_size() << std::endl;

	std::string* myString = stringAlloc.allocate(3);

	stringAlloc.construct(myString, "Hello");
	stringAlloc.construct(myString + 1, "World");
	stringAlloc.construct(myString + 2, "!");

	std::cout << myString[0] << " " << myString[1] << " " << myString[2] << std::endl;

	stringAlloc.destroy(myString);
	stringAlloc.destroy(myString + 1);
	stringAlloc.destroy(myString + 2);
	stringAlloc.deallocate(myString, 3);

	std::cout << std::endl;

	return 0;
}

//////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/memory/allocator
int test_allocator_4()
{
	std::allocator<int> a1;   // default allocator for ints
	int* a = a1.allocate(1);  // space for one int
	a1.construct(a, 7);       // construct the int
	std::cout << a[0] << '\n';
	a1.deallocate(a, 1);      // deallocate space for one int

	// default allocator for strings
	std::allocator<std::string> a2;

	// same, but obtained by rebinding from the type of a1
	decltype(a1)::rebind<std::string>::other a2_1;

	// same, but obtained by rebinding from the type of a1 via allocator_traits
	std::allocator_traits<decltype(a1)>::rebind_alloc<std::string> a2_2;

	std::string* s = a2.allocate(2); // space for 2 strings

	a2.construct(s, "foo");
	a2.construct(s + 1, "bar");

	std::cout << s[0] << ' ' << s[1] << '\n';

	a2.destroy(s);
	a2.destroy(s + 1);
	a2.deallocate(s, 2);

	return 0;
}

} // namespace allocator_

