#ifndef FBC_MESSY_TEST_BRIDGE_HPP_
#define FBC_MESSY_TEST_BRIDGE_HPP_

#include <iostream>

// ==================================================
//�ֻ����
class HandsetSoft
{
public:
	virtual void Run() = 0;
};

//��Ϸ���
class HandsetGame : public HandsetSoft
{
public:
	virtual void Run()
	{
		std::cout << "�����ֻ���Ϸ" << std::endl;
	}
};

//ͨѶ¼���
class HandSetAddressList : public HandsetSoft
{
public:
	virtual void Run()
	{
		std::cout << "�ֻ�ͨѶ¼" << std::endl;
	}
};

//�ֻ�Ʒ��
class HandsetBrand
{
protected:
	HandsetSoft* m_soft;
public:
	void SetHandsetSoft(HandsetSoft* temp)
	{
		m_soft = temp;
	}
	virtual void Run() = 0;
};

//MƷ��
class HandsetBrandM : public HandsetBrand
{
public:
	virtual void Run()
	{
		m_soft->Run();
	}
};

//NƷ��
class HandsetBrandN : public HandsetBrand
{
public:
	virtual void Run()
	{
		m_soft->Run();
	}
};

// ========================================================
class AbstractionImp;

class Abstraction
{
public:
	virtual ~Abstraction();
	virtual void Operation() = 0;
protected:
	Abstraction();
private:
};

class RefinedAbstraction : public Abstraction
{
public:
	RefinedAbstraction(AbstractionImp* imp);
	~RefinedAbstraction();
	void Operation();
protected:
private:
	AbstractionImp* _imp;
};

int test_Bridge1(); // �ͻ���
int test_Bridge2();

#endif // FBC_MESSY_TEST_BRIDGE_HPP_

