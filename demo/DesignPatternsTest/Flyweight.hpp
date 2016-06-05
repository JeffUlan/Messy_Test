#ifndef FBC_MESSY_TEST_FLYWEIGHT_HPP_
#define FBC_MESSY_TEST_FLYWEIGHT_HPP_

#include <vector>
#include <string>
#include <iostream>

//�������վ
class WebSite
{
public:
	virtual void Use() = 0;
};

//����Ĺ�����վ
class ConcreteWebSite : public WebSite
{
private:
	std::string name;
public:
	ConcreteWebSite(std::string strName)
	{
		name = strName;
	}

	virtual void Use()
	{
		std::cout << "��վ����:" << name << std::endl;
	}
};

//���������վ
class UnShareWebSite : public WebSite
{
private:
	std::string name;
public:
	UnShareWebSite(std::string strName)
	{
		name = strName;
	}

	virtual void Use()
	{
		std::cout << "���������վ:" << name << std::endl;
	}
};

//��վ�����࣬���ڴ�Ź����WebSite����
class WebFactory
{
private:
	std::vector<WebSite*> websites;
public:
	WebSite* GetWeb()
	{
		std::vector<WebSite*>::iterator p = websites.begin();
		return *p;
	}

	WebFactory()
	{
		websites.push_back(new ConcreteWebSite("����"));
	}
};

// =====================================
class Flyweight
{
public:
	virtual ~Flyweight();
	virtual void Operation(const std::string& extrinsicState);
	std::string GetIntrinsicState();
protected:
	Flyweight(std::string intrinsicState);
private:
	std::string _intrinsicState;
};

class ConcreteFlyweight : public Flyweight
{
public:
	ConcreteFlyweight(std::string intrinsicState);
	~ConcreteFlyweight();
	void Operation(const std::string& extrinsicState);
protected:
private:
};

int test_Flyweight1();
int test_Flyweight2();

#endif // FBC_MESSY_TEST_FLYWEIGHT_HPP_
