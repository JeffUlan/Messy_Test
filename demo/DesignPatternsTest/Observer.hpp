#ifndef FBC_MESSY_TEST_OBSERVER_HPP_
#define FBC_MESSY_TEST_OBSERVER_HPP_

#include <string>
#include <iostream>
#include <vector>

#include "Subject.hpp"

class Secretary;

//����Ʊ��ͬ����(�۲���󣬹۲���)
class StockObserver
{
private:
	std::string name;
	Secretary* sub;
public:
	StockObserver(std::string strname, Secretary* strsub)
	{
		name = strname;
		sub = strsub;
	}

	void Update();
};

//������(�������֪ͨ��)
class Secretary
{
private:
	std::vector<StockObserver> observers;
public:
	std::string action;
	void Add(StockObserver ob)
	{
		observers.push_back(ob);
	}

	void Notify()
	{
		std::vector<StockObserver>::iterator p = observers.begin();

		while (p != observers.end())
		{
			(*p).Update();
			p++;
		}
	}
};

// ===========================================================
class SecretaryBase;

//����۲���
class CObserverBase
{
protected:
	std::string name;
	SecretaryBase* sub;
public:
	CObserverBase(std::string strname, SecretaryBase* strsub)
	{
		name = strname;
		sub = strsub;
	}

	virtual void Update() = 0;
};

//����Ĺ۲��ߣ�����Ʊ��
class StockObserver_1 : public CObserverBase
{
public:
	StockObserver_1(std::string strname, SecretaryBase* strsub) : CObserverBase(strname, strsub)
	{

	}

	virtual void Update();
};

//����۲��ߣ���NBA��
class NBAObserver : public CObserverBase
{
public:
	NBAObserver(std::string strname, SecretaryBase* strsub) : CObserverBase(strname, strsub)
	{

	}

	virtual void Update();
};

//����֪ͨ��
class SecretaryBase
{
public:
	std::string action;
	std::vector<CObserverBase*> observers;
public:
	virtual void Attach(CObserverBase* observer) = 0;
	virtual void Notify() = 0;
};

//����֪ͨ��
class Secretary_1 : public SecretaryBase
{
public:
	void Attach(CObserverBase* ob)
	{
		observers.push_back(ob);
	}

	void Notify()
	{
		std::vector<CObserverBase*>::iterator p = observers.begin();

		while (p != observers.end())
		{
			(*p)->Update();
			p++;
		}
	}
};

// =========================================================
class Observer
{
public:
	virtual ~Observer();
	virtual void Update(Subject* sub) = 0;
	virtual void PrintInfo() = 0;
protected:
	Observer();
	State _st;
private:
};

class ConcreteObserverA : public Observer
{
public:
	virtual Subject* GetSubject();
	ConcreteObserverA(Subject* sub);
	virtual ~ConcreteObserverA();

	//����Subject��Ϊ����������������һ��View���ڶ����Subject
	void Update(Subject* sub);
	void PrintInfo();
protected:
private:
	Subject* _sub;
};

class ConcreteObserverB : public Observer
{
public:
	virtual Subject* GetSubject();
	ConcreteObserverB(Subject* sub);
	virtual ~ConcreteObserverB();
	//����Subject��Ϊ����������������һ��View���ڶ����Subject
	void Update(Subject* sub);
	void PrintInfo();
protected:
private:
	Subject* _sub;
};

int test_Observer1();
int test_Observer2();
int test_Observer3();

#endif // FBC_MESSY_TEST_OBSERVER_HPP_
