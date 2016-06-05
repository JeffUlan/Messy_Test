#ifndef FBC_MESSY_TEST_CHAIN_OF_RESPONSIBILITY_HPP_
#define FBC_MESSY_TEST_CHAIN_OF_RESPONSIBILITY_HPP_

#include <iostream>
#include <string>

//����
class Request
{
public:
	std::string m_strContent;
	int m_nNumber;
};

//������
class Manager
{
protected:
	Manager* manager;
	std::string name;
public:
	Manager(std::string temp)
	{
		name = temp;
	}

	void SetSuccessor(Manager* temp)
	{
		manager = temp;
	}

	virtual void GetRequest(Request* request) = 0;
};

//����
class CommonManager : public Manager
{
public:
	CommonManager(std::string strTemp) : Manager(strTemp) {}

	virtual void GetRequest(Request* request)
	{
		if (request->m_nNumber >= 0 && request->m_nNumber < 10)
			std::cout << name << "������" << request->m_nNumber << "������" << std::endl;
		else
			manager->GetRequest(request);
	}
};

//�ܼ�
class MajorDomo : public Manager
{
public:
	MajorDomo(std::string name) : Manager(name) {}

	virtual void GetRequest(Request* request)
	{
		if (request->m_nNumber >= 10)
			std::cout << name << "������" << request->m_nNumber << "������" << std::endl;
	}
};

int test_ChainOfResponsibility1();
int test_ChainOfResponsibility2();

#endif // FBC_MESSY_TEST_CHAIN_OF_RESPONSIBILITY_HPP_