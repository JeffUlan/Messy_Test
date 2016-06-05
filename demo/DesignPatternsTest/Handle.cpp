#include "Handle.hpp"
#include <iostream>

Handle::Handle()
{
	_succ = 0;
}

Handle::~Handle()
{
	delete _succ;
}

Handle::Handle(Handle* succ)
{
	this->_succ = succ;
}

void Handle::SetSuccessor(Handle* succ)
{
	_succ =  succ;
}

Handle* Handle::GetSuccessor()
{
	return _succ;
}

void Handle::HandleRequest()
{

}

ConcreteHandleA::ConcreteHandleA()
{

}

ConcreteHandleA::ConcreteHandleA(Handle* succ) : Handle(succ)
{

}

ConcreteHandleA::~ConcreteHandleA()
{

}

void ConcreteHandleA::HandleRequest()
{
	if (this->GetSuccessor() != 0) {
		std::cout << "ConcreteHandleA �ҰѴ���Ȩ����̽ڵ� ..." << std::endl;
		this->GetSuccessor()->HandleRequest();
	} else
		std::cout << "ConcreteHandleA û�к���ˣ� �ұ����Լ����� ..." << std::endl;
}

ConcreteHandleB::ConcreteHandleB()
{

}

ConcreteHandleB::ConcreteHandleB(Handle* succ) : Handle(succ)
{

}

ConcreteHandleB::~ConcreteHandleB()
{

}

void ConcreteHandleB::HandleRequest()
{
	if (this->GetSuccessor() != 0) {
		std::cout << "ConcreteHandleB �ҰѴ���Ȩ����̽ڵ� ..." << std::endl;
		this->GetSuccessor()->HandleRequest();
	} else
		std::cout << "ConcreteHandleB û�к���ˣ��ұ����Լ����� ..." << std::endl;
}