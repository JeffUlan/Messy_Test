#include "Command.hpp"
#include "Receiver.hpp"
#include "Invoker.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/36221901

Command_1::Command_1()
{

}

Command_1::~Command_1()
{

}

void Command_1::Excute()
{

}

ConcreteCommand::ConcreteCommand(Receiver* rev)
{
	this->_rev = rev;
}

ConcreteCommand::~ConcreteCommand()
{
	delete this->_rev;
}

void ConcreteCommand::Excute()
{
	_rev->Action();
	std::cout << "ConcreteCommand ..." << std::endl;
}

int test_Command1()
{
	//������ӿ���ʦ�����˵�������Ա�ȹ˿�
	Barbucer* barbucer = new Barbucer();
	Command* cmd = new BakeMuttonCmd(barbucer);
	Command* cmd2 = new ChickenWingCmd(barbucer);
	Waiter* girl = new Waiter();

	//���
	girl->SetCmd(cmd);
	girl->SetCmd(cmd2);

	//����Ա֪ͨ
	girl->Notify();

	/*result
		���Ӷ���
		���Ӷ���
		������
		�������
	*/

	return 0;
}

int test_Command2()
{
	Receiver* rev = new Receiver();
	Command_1* cmd = new ConcreteCommand(rev);
	Invoker* inv = new Invoker(cmd);
	inv->Invoke();

	/*result
		Receiver action ...
		ConcreteCommand ...
	*/

	return 0;
}
