#ifndef FBC_MESSY_TEST_COMMAND_HPP_
#define FBC_MESSY_TEST_COMMAND_HPP_

#include <iostream>
#include <vector>

//����ʦ��
class Barbucer
{
public:
	void MakeMutton()
	{
		std::cout << "������" << std::endl;
	}

	void MakeChickenWing()
	{
		std::cout << "�������" << std::endl;
	}
};

//����������
class Command {
protected:
	Barbucer* receiver;
public:
	Command(Barbucer* temp)
	{
		receiver = temp;
	}

	virtual void ExecuteCmd() = 0;
};

//����������
class BakeMuttonCmd : public Command
{
public:
	BakeMuttonCmd(Barbucer* temp) : Command(temp) {}
	virtual void ExecuteCmd()
	{
		receiver->MakeMutton();
	}
};

//������
class ChickenWingCmd : public Command
{
public:
	ChickenWingCmd(Barbucer* temp) : Command(temp) {}

	virtual void ExecuteCmd()
	{
		receiver->MakeChickenWing();
	}
};

//����Ա��
class Waiter
{
protected:
	std::vector<Command*> m_commandList;
public:
	void SetCmd(Command* temp)
	{
		m_commandList.push_back(temp);
		std::cout << "���Ӷ���" << std::endl;
	}

	//ִ֪ͨ��
	void Notify()
	{
		std::vector<Command*>::iterator p = m_commandList.begin();

		while (p != m_commandList.end()) {
			(*p)->ExecuteCmd();
			p++;
		}
	}
};

// =================================================
class Receiver;

class Command_1
{
public:
	virtual ~Command_1();
	virtual void Excute() = 0;
protected:
	Command_1();
private:
};

class ConcreteCommand : public Command_1
{
public:
	ConcreteCommand(Receiver* rev);
	~ConcreteCommand();
	void Excute();
protected:
private:
	Receiver* _rev;
};

int test_Command1();
int test_Command2();

#endif // FBC_MESSY_TEST_COMMAND_HPP_
