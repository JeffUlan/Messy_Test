#include "ChainOfResponsibility.hpp"
#include "Handle.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/37111697

int test_ChainOfResponsibility1()
{
	Manager* common = new CommonManager("�ž���");
	Manager* major = new MajorDomo("���ܼ�");

	common->SetSuccessor(major);

	Request* req = new Request();
	req->m_nNumber = 33;
	common->GetRequest(req);

	req->m_nNumber = 3;
	common->GetRequest(req);

	/*result
		���ܼദ����33������
		�ž�������3������
	*/

	return 0;
}

int test_ChainOfResponsibility2()
{
	Handle* h1 = new ConcreteHandleA();
	Handle* h2 = new ConcreteHandleB();

	h1->SetSuccessor(h2);
	h1->HandleRequest();

	/*result
		ConcreteHandleA �ҰѴ���Ȩ����̽ڵ� ...
		ConcreteHandleB û�к���ˣ��ұ����Լ����� ...
	*/

	return 0;
}
