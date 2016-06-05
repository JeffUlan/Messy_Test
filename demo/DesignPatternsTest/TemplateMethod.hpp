#ifndef FBC_MESSY_TEST_TEMPLATE_METHOD_HPP_
#define FBC_MESSY_TEST_TEMPLATE_METHOD_HPP_

#include <iostream>
#include <string>

class AbstractClass
{
public:
	void Show()
	{
		std::cout << "����" << GetName() << std::endl;
	}
protected:
	virtual std::string GetName() = 0;
};

class Naruto : public AbstractClass
{
protected:
	virtual std::string GetName()
	{
		return "��Ӱʷ����˧������Ŀ----һ������naruto";
	}
};

class OnePice : public AbstractClass
{
protected:
	virtual std::string GetName()
	{
		return "�����޶����Ĵ���----·��";
	}
};

// ====================================================
class AbstractClass_1
{
public:
	virtual ~AbstractClass_1();
	void TemplateMethod();
protected:
	virtual void PrimitiveOperation1() = 0;
	virtual void PrimitiveOperation2() = 0;
	AbstractClass_1();
private:
};

class ConcreteClass1_1 : public AbstractClass_1
{
public:
	ConcreteClass1_1();
	~ConcreteClass1_1();
protected:
	void PrimitiveOperation1();
	void PrimitiveOperation2();
private:
};

class ConcreteClass2_1 : public AbstractClass_1
{
public:
	ConcreteClass2_1();
	~ConcreteClass2_1();
protected:
	void PrimitiveOperation1();
	void PrimitiveOperation2();
private:
};

int test_TemplateMethod1();
int test_TemplateMethod2();

#endif // FBC_MESSY_TEST_TEMPLATE_METHOD_HPP_
