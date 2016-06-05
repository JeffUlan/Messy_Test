#ifndef FBC_MESSY_TEST_ADAPTER_HPP_
#define FBC_MESSY_TEST_ADAPTER_HPP_

#include <iostream>
#include <string>

// =====================================================
class Target_
{
public:
	virtual void Request()
	{
		std::cout << "��ͨ������" << std::endl;
	}
};

class Adaptee_
{
public:
	void SpecificalRequest()
	{
		std::cout << "���������" << std::endl;
	}
};

class Adapter_ : public Target_
{
private:
	Adaptee_* ada;
public:
	virtual void Request()
	{
		ada->SpecificalRequest();
		Target_::Request();
	}

	Adapter_()
	{
		ada = new Adaptee_();
	}

	~Adapter_()
	{
		delete ada;
	}
};

// =================================================
class Player
{
protected:
	std::string name;
public:
	Player(std::string strName) { name = strName; }
	virtual void Attack() = 0;
	virtual void Defense() = 0;
};

class Forwards : public Player
{
public:
	Forwards(std::string strName) : Player(strName) {}
public:
	virtual void Attack()
	{
		std::cout << name << "ǰ�����" << std::endl;
	}

	virtual void Defense()
	{
		std::cout << name << "ǰ�����" << std::endl;
	}
};

class Center : public Player
{
public:
	Center(std::string strName) : Player(strName) {}
public:
	virtual void Attack()
	{
		std::cout << name << "�г�����" << std::endl;
	}

	virtual void Defense()
	{
		std::cout << name << "�г�����" << std::endl;
	}
};

//Ϊ�г�����
class TransLater : public Player
{
private:
	Center* player;
public:
	TransLater(std::string strName) : Player(strName)
	{
		player = new Center(strName);
	}

	virtual void Attack()
	{
		player->Attack();
	}

	virtual void Defense()
	{
		player->Defense();
	}
};

// ======================================================
class Target
{
public:
	Target();
	virtual ~Target();
	virtual void Request();
protected:
private:
};

class Adaptee
{
public:
	Adaptee();
	~Adaptee();
	void SpecificRequest();
protected:
private:
};

class Adapter : public Target, private Adaptee
{
public:
	Adapter();
	~Adapter();
	void Request();
protected:
private:
};

// ============================================================
class Target4
{
public:
	Target4();
	virtual ~Target4();
	virtual void Request();

protected:
private:
};

class Adaptee4
{
public:
	Adaptee4();
	~Adaptee4();
	void SpecificRequest();

protected:
private:
};

class Adapter4 : public Target4
{
public:
	Adapter4(Adaptee4* ade);
	~Adapter4();
	void Request();
protected:
private:
	Adaptee4* _ade;
};

int test_Adapter1(); // �ͻ���
int test_Adapter2(); // �ͻ���
int test_Adapter3();
int test_Adapter4();

#endif // FBC_MESSY_TEST_ADAPTER_HPP_
