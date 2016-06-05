#ifndef FBC_MESSY_TEST_VISITOR_HPP_
#define FBC_MESSY_TEST_VISITOR_HPP_

#include <iostream>
#include <vector>

class Man;
class Woman;

//��Ϊ
class Action
{
public:
	virtual void GetManConclusion(Man* concreteElementA) = 0;
	virtual void GetWomanConclusion(Woman* concreteElementB) = 0;
};

//�ɹ�
class Success : public Action
{
public:
	virtual void GetManConclusion(Man* concreteElementA)
	{
		std::cout << "���˳ɹ�ʱ�������и�ΰ���Ů��" << std::endl;
	}

	virtual void GetWomanConclusion(Woman* concreteElementB)
	{
		std::cout << "Ů�˳ɹ�ʱ�������и�û�õ�����" << std::endl;
	}
};

//ʧ��
class Failure : public Action
{
public:
	virtual void GetManConclusion(Man* concreteElementA)
	{
		std::cout << "����ʧ��ʱ�������и�ΰ���Ů��" << std::endl;
	}

	virtual void GetWomanConclusion(Woman* concreteElementB)
	{
		std::cout << "Ů��ʧ��ʱ�������и�û�õ�����" << std::endl;
	}
};

//��������
class Person_2
{
public:
	virtual void Accept(Action* visitor) = 0;
};

//����
class Man : public Person_2
{
public:
	virtual void Accept(Action* visitor)
	{
		visitor->GetManConclusion(this);
	}
};

//Ů��
class Woman : public Person_2
{
public:
	virtual void Accept(Action* visitor)
	{
		visitor->GetWomanConclusion(this);
	}
};

//����ṹ��
class ObjectStructure
{
private:
	std::vector<Person_2*> m_personList;
public:
	void Add(Person_2* p)
	{
		m_personList.push_back(p);
	}

	void Display(Action* a)
	{
		std::vector<Person_2*>::iterator p = m_personList.begin();

		while (p != m_personList.end()) {
			(*p)->Accept(a);
			p++;
		}
	}
};

// =============================================
class ConcreteElementA;
class ConcreteElementB;
class Element;

class Visitor
{
public:
	virtual ~Visitor();
	virtual void VisitConcreteElementA(Element* elm) = 0;
	virtual void VisitConcreteElementB(Element* elm) = 0;
protected:
	Visitor();
private:
};

class ConcreteVisitorA : public Visitor
{
public:
	ConcreteVisitorA();
	virtual ~ConcreteVisitorA();
	virtual void VisitConcreteElementA(Element* elm);
	virtual void VisitConcreteElementB(Element* elm);
protected:
private:
};

class ConcreteVisitorB : public Visitor
{
public:
	ConcreteVisitorB();
	virtual ~ConcreteVisitorB();
	virtual void VisitConcreteElementA(Element* elm);
	virtual void VisitConcreteElementB(Element* elm);
protected:
private:
};

int test_Visitor1();
int test_Visitor2();

#endif // FBC_MESSY_TEST_VISITOR_HPP_
