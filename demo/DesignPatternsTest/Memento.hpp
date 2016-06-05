#ifndef FBC_MESSY_TEST_MEMENTO_HPP_
#define FBC_MESSY_TEST_MEMENTO_HPP_

#include <string>
#include <iostream>

class Memo_1;

//��������
class Originator_1
{
public:
	std::string state;
	Memo_1* CreateMemo();
	void SetMemo(Memo_1* memo);
	void Show()
	{
		std::cout << "״̬" << state << std::endl;
	}
};

//����¼��
class Memo_1
{
public:
	std::string state;
	Memo_1(std::string strState)
	{
		state = strState;
	}
};

//��������
class Caretaker_1
{
public:
	Memo_1* memo;
};

// =================================================
class Memento;

class Originator_2
{
public:
	typedef std::string State;
	Originator_2();
	Originator_2(const State& sdt);
	~Originator_2();
	Memento* CreateMemento();
	void SetMemento(Memento* men);
	void RestoreToMemento(Memento* mt);
	State GetState();
	void SetState(const State& sdt);
	void PrintState();
protected:
private:
	State _sdt;
	Memento* _mt;
};

class Memento
{
public:
protected:
private:
	//������ؼ��ĵط�����OriginatorΪfriend�࣬���Է����ڲ���Ϣ�����������಻�ܷ���
	friend class Originator_2;
	typedef std::string State;
	Memento();
	Memento(const State& sdt);
	~Memento();
	void SetState(const State& sdt);
	State GetState();
private:
	State _sdt;
};

int test_Memento1();
int test_Memento2();

#endif // FBC_MESSY_TEST_MEMENTO_HPP_
