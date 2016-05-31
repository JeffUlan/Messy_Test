#include <iostream>
#include "template.hpp"

template <typename T>
const T& max_mum(const T& x, const T& y)
{
	if (y > x){
		return y;
	}
	else{
		return x;
	}
}

// ����ģ�������붨��ֿ�������ģ����ʾʵ����
template const int& max_mum<int>(const int&, const int&);

template<class T>
void A<T>::f()
{
	std::cout << " template class impl" << std::endl;
}

// ��ģ�������붨��ֿ�����ģ����ʾʵ����
template class A < int > ;
