#ifndef FBC_MESSY_TEST_STATE_HPP_
#define FBC_MESSY_TEST_STATE_HPP_

#include <iostream>

class Work;
class ForenoonState;
class NoonState;

class State_
{
public:
	virtual void WriteProgram(Work* w) = 0;
};

class Work
{
private:
	State_* current;
public:
	double hour;
public:
	Work();
	void SetState(State_* temp)
	{
		current = temp;
	}

	void Writeprogram()
	{
		current->WriteProgram(this);
	}
};

class NoonState : public State_
{
public:
	virtual void WriteProgram(Work* w)
	{
		std::cout << "execute" << std::endl;

		if ((w->hour) < 13)
			std::cout << "��������" << std::endl;
		else
			std::cout << "�����ˣ�����˯����" << std::endl;
	}
};

class ForenoonState : public State_
{
public:
	virtual void WriteProgram(Work* w)
	{
		if ((w->hour) < 12)
			std::cout << "���ڵľ����޵к�" << std::endl;
		else {
			w->SetState(new NoonState());
			w->Writeprogram();//ע��������
		}

	}
};


int test_State1();
int test_State2();

#endif // FBC_MESSY_TEST_STATE_HPP_
