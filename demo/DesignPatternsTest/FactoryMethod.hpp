#ifndef FBC_MESSY_TEST_FACTORY_METHOD_HPP_
#define FBC_MESSY_TEST_FACTORY_METHOD_HPP_

#include <iostream>

//ʵ�����࣬�൱��Product��Ϊ�˷��㣬û�ó���
class LeiFeng
{
public:
	virtual void Sweep()
	{
		std::cout << "�׷�ɨ��" << std::endl;
	}
};

//ѧ�׷�Ĵ�ѧ���൱��ConcreteProduct
class Student : public LeiFeng
{
public:
	virtual void Sweep()
	{
		std::cout << "��ѧ��ɨ��" << std::endl;
	}
};

//ѧ�׷��־Ը�ߣ��൱��ConcreteProduct
class Volenter : public LeiFeng
{
public:
	virtual void Sweep()
	{
		std::cout << "־Ը��ɨ��" << std::endl;
	}
};

//�������� Creator
class LeiFangFactory
{
public:
	virtual LeiFeng* CreateLeiFeng()
	{
		return new LeiFeng();
	}
};

//����������
class StudentFactory : public LeiFangFactory
{
public:
	virtual LeiFeng* CreateLeiFeng()
	{
		return new Student();
	}
};

class VolenterFactory : public LeiFangFactory
{
public:
	virtual LeiFeng* CreateLeiFeng()
	{
		return new Volenter();
	}
};



int test_FactoryMethod1();
int test_FactoryMethod2();

#endif // FBC_MESSY_TEST_FACTORY_METHOD_HPP_
