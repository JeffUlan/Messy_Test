#include <vector>
#include <iostream>
#include <assert.h>

#include "vector.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/51510916

int test_vector_init()
{
	std::vector<int> a; // ����һ��int������a,sizeΪ0
	std::vector<int> b(10); // ����һ����ʼsizeΪ10������
	std::vector<int> c(10, 1); // ����һ����ʼsizeΪ10�ҳ�ʼֵ��Ϊ1������
	std::vector<int> d(b); // ������������b��ʼ������d
	std::vector<int> e(c.begin(), c.begin() + 3); // ��c�����дӵ�0������2��(��3��)��Ϊ����e�ĳ�ʼֵ,sizeΪ3

	int n[] = { 1, 2, 3, 4, 5 };
	std::vector<int> f(n, n + 5); // ������n��ǰ5��Ԫ����Ϊ����f�ĳ�ֵ,sizeΪ5
	std::vector<int> g(&n[1], &n[4]); // ��n[1] - n[4]��Χ�ڵ�Ԫ����Ϊ����g�ĳ�ֵ,sizeΪ3

	std::vector<std::string> v(5, "hello");
	std::vector<std::string> v2(v.begin(), v.end());
	assert(v == v2);

	assert(v.begin() + v.size() == v.end());
	assert(v.end() - v.size() == v.begin());

	std::vector<int> array{ 9, 7, 5, 3, 1 };
	std::cout << "array size: "<< array.size() << std::endl; // 5

	return 0;
}

int test_vector_access()
{
	int n[10];
	for (int i = 0; i < 10; i++) {
		n[i] = i;
	}

	std::vector<int> a(n, n + 10);

	// �����в���Ԫ�ؽ�������
	std::cin >> a[2];
	std::cin >> a[5];
	std::cin >> a[6];

	// ���
	for (int i = 0; i < a.size(); i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

	// ʹ�ñ�����(�ֳƵ�����)�������
	// vector��ĵ���������֧��ͨ�õ�ǰ׺����������⣬��֧���������㣺it + n��it - n��it2 - it1
	std::vector<int>::iterator t;
	for (t = a.begin(); t != a.end(); t++) {
		std::cout << *t << " ";
	}
	std::cout << std::endl;

	for (std::vector<int>::const_iterator p = a.begin(); p != a.end(); p++) {
		std::cout << *p << " ";
	}
	std::cout << std::endl;

	size_t i = 0;
	int* x = a.data(); //����ָ���ڴ��������һ��Ԫ�ص�ָ��
	*x = -111;
	std::cout << "a[0]: " << a[0] << std::endl; // -111

	return 0;
}

int test_vector_operation()
{
	int n[10], m[15];
	for (int i = 0; i < 10; i++) {
		n[i] = i;
		m[i] = i + 20;
	}

	std::vector<int> a(n, n + 10);
	std::vector<int> b(m, m + 15);
	std::vector<int> x;
	x = a; // ��ֵ

	std::cout << "x size: "<<a.size() << std::endl; // ��ȡ�����е�Ԫ�ظ���, 10
	std::cout << "x capacity: " << x.capacity() << std::endl; // ���ص�ǰ�洢�ռ��ܹ����ɵ�Ԫ����������x�ܹ��洢��Ԫ�ظ�����10 (x.capacity() >= x.size())
	std::cout << "x max size: " << x.max_size() << std::endl; // ����x�����ɵ����Ԫ�ظ���, 4611686018427387903
	x.reserve(15); // Ԥ���洢�ռ䣬ȷ��x.capacity() >= 15
	std::cout << "x capacity after reserve: " << x.capacity() << std::endl; // 15
	x.shrink_to_fit();
	x.resize(5); // �ı������пɴ洢Ԫ�صĸ���,ȷ�����غ���x.size() == 5, ���֮ǰx.size() < 5, ��ô��Ĭ��ֵ��ȫ
	std::cout << "x size after resize: " << x.size() << std::endl; // 5

	std::vector<int>::reference ref1 = b.front(); // ���������е�һ��Ԫ�ص�����(��������ǿ�), 20
	std::vector<int>::reference ref2 = x.back(); // �������������һ��Ԫ�ص�����(��������ǿ�), 4
	int value = b[5]; // �����±�Ϊ5��Ԫ�ص�����(�±��0��ʼ������±겻��ȷ��������δ������Ϊ)�� 25
	std::vector<int>::reference ref3 = b.at(5); // �����±�Ϊpos��Ԫ�ص����ã�����±겻��ȷ�����׳��쳣, 25
	x.push_back(-100); // ��Ԫ����ӵ�����ĩβ,������ĩβ���һ��Ԫ��
	value = x[x.size() - 1]; // -100
	std::cout << "x size after push_back: " << x.size() << std::endl; // 6
	x.pop_back(); // ɾ�����һ��Ԫ��, �������������һ��Ԫ�أ���������ǿգ�
	value = x[x.size() - 1]; // 4
	std::cout << "x size after pop_back: " << x.size() << std::endl; // 5

	x.assign(10, -1); // ��ֵ����ָ��Ԫ�������滻����������Ԫ��
	std::cout << "x size after assign: " << x.size() << std::endl; // 10
	std::cout << "x[0]: " << x[0] << std::endl; // -1

	std::cout << "a is empty: "<< a.empty() << std::endl; // �ж������Ƿ�Ϊ��, 0
	std::cout << "a size: " << a.size() << std::endl; // ��ȡ�����е�Ԫ�ظ���, 10
	a.clear(); // ɾ��ȫ������, ��������е�Ԫ��,�൱�ڵ���erase(begin(), end())
	std::cout << "size after clear: " << a.size() << std::endl; // 0

	std::vector<int> c;
	c = b; // ��b�������Ƶ�c������

	std::cout << "a == b ?: " << (a == b) << std::endl; // == �� != ��>�� >= ��<�� <= , �����ֵ�������ԱȽ�,a������b�����Ƚ�, ����򷵻�1, 0
	std::cout << "c == b ?: " << (c == b) << std::endl; // == �� != ��>�� >= ��<�� <= , �����ֵ�������ԱȽ�,c������b�����Ƚ�, ����򷵻�1, 1

	// �����ɾ������������Ԫ�ص��ƶ���Ϊ�˱��������洢�����ʣ�������֮ǰ�ĵ���������ʧЧ
	// �κθı�������С�Ĳ��������������ǰ�ĵ�����ʧЧ
	std::cout << "b size: " << b.size() << std::endl; // 15
	b.insert(b.begin(), -1); // ��-1���뵽����b����ʼλ��ǰ
	std::cout << "b[0]: " << b[0] << std::endl; // -1
	std::cout << "b size: " << b.size() << std::endl; // 16

	b.insert(b.begin() + 5, 3, -1); //��-1�ֱ���뵽����Ԫ��λ�õ�5-8��(��3��Ԫ��)
	for (int i = 0; i < b.size(); i++) {
		std::cout << b[i] << "  "; // -1 20 21 22 23 -1 -1 -1 24 25 ...
	}
	std::cout<<std::endl;

	std::vector<int> d(5, 1);
	std::vector<int> e(10);
	e.insert(e.begin(), d.begin(), d.end()); //��d.begin(), d.end()֮���ȫ��Ԫ�ز��뵽e.begin()ǰ
	for (int i = 0; i < e.size(); i++) {
		std::cout << e[i] << "  "; // 1 1 1 1 1 0 0 0 ...
	}
	std::cout << std::endl;

	std::cout << "b size: " << b.size() << std::endl; // 19
	b.erase(b.begin()); // ����ʼλ�õ�Ԫ��ɾ��
	std::cout << "b size: " << b.size() << std::endl; // 18
	b.erase(b.begin(), b.begin() + 3); // ��(b.begin(), b.begin()+3)֮���Ԫ��ɾ��
	std::cout << "b size: " << b.size() << std::endl; // 15

	b.swap(c); // ����vector������, a������c�������н���
	for (int i = 0; i < b.size(); i++) {
		std::cout << b[i] << "  ";
	}
	std::cout << std::endl;

	for (int i = 0; i < c.size(); i++) {
		std::cout << c[i] << "  ";
	}
	std::cout << std::endl;

	return 0;
}

int test_vector_two_dimension()
{
	// reference: http://www.cnblogs.com/mr-wid/archive/2013/01/22/2871105.html

	std::vector< std::vector<int> > b(10, std::vector<int>(5, -1));

	// �Բ������ݽ�������
	std::cin >> b[1][1];
	std::cin >> b[2][2];
	std::cin >> b[3][3];

	// ȫ�����
	for (int m = 0; m < b.size(); m++) { //b.size()��ȡ�������Ĵ�С
		for (int n = 0; n < b[m].size(); n++) { //��ȡ�����о���ÿ�������Ĵ�С
			std::cout << b[m][n] << "  ";
		}
		std::cout << std::endl;
	}

	return 0;
}

