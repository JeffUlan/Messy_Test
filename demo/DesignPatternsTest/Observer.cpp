#include "Observer.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/34933089

void StockObserver::Update()
{
	std::cout << name << ":" << sub->action << "����Ҫ���Ʊ�ˣ�Ҫ��ʼ������" << std::endl;
}

void StockObserver_1::Update()
{
	std::cout << name << ":" << sub->action << "��Ҫ���Ʊ�ˣ�Ҫ��ʼ������" << std::endl;
}

void NBAObserver::Update()
{
	std::cout << name << ":" << sub->action << "��Ҫ��NBA�ˣ��ϰ�����" << std::endl;
}

Observer::Observer()
{
	_st = '\0';
}

Observer::~Observer()
{

}

ConcreteObserverA::ConcreteObserverA(Subject* sub)
{
	_sub = sub;
	_sub->Attach(this);
}

ConcreteObserverA::~ConcreteObserverA()
{
	_sub->Detach(this);

	if (_sub != 0)
		delete _sub;
}

Subject* ConcreteObserverA::GetSubject()
{
	return _sub;
}

void ConcreteObserverA::PrintInfo()
{
	std::cout << "ConcreteObserverA observer ..." << _sub->GetState() << std::endl;
}

void ConcreteObserverA::Update(Subject* sub)
{
	_st = sub->GetState();
	PrintInfo();
}

ConcreteObserverB::ConcreteObserverB(Subject* sub)
{
	_sub = sub;
	_sub->Attach(this);
}

ConcreteObserverB::~ConcreteObserverB()
{
	_sub->Detach(this);

	if (_sub != 0)
		delete _sub;
}

Subject* ConcreteObserverB::GetSubject()
{
	return _sub;
}

void ConcreteObserverB::PrintInfo()
{
	std::cout << "ConcreteObserverB observer ..." << _sub->GetState() << std::endl;
}

void ConcreteObserverB::Update(Subject* sub)
{
	_st = sub->GetState();
	PrintInfo();
}


int test_Observer1()
{
	Secretary* p = new Secretary();//����֪ͨ��

	//�۲���
	StockObserver* s1 = new StockObserver("С��", p);
	StockObserver* s2 = new StockObserver("С��", p);

	//����֪ͨ����
	p->Add(*s1);
	p->Add(*s2);

	//�¼�
	p->action = "�ϰ�����";

	//֪ͨ
	p->Notify();

	/*result
		С��ϰ����ˣ���Ҫ���Ʊ�ˣ�Ҫ��ʼ������
		С�ԣ��ϰ����ˣ���Ҫ���Ʊ�ˣ�Ҫ��ʼ������
	*/

	return 0;
}

int test_Observer2()
{
	SecretaryBase* p = new Secretary_1();//�����۲���

	//���۲�Ķ���
	CObserverBase* s1 = new NBAObserver("С��", p);
	CObserverBase* s2 = new StockObserver_1("С��", p);
	//����۲����
	p->Attach(s1);
	p->Attach(s2);
	//�¼�
	p->action = "�ϰ�����";
	//֪ͨ
	p->Notify();

	/*result
		С��ϰ����˲�Ҫ��NBA�ˣ��ϰ�����
		С�ԣ��ϰ����˲�Ҫ���Ʊ�ˣ�Ҫ��ʼ������
	*/

	return 0;
}

int test_Observer3()
{
	ConcreteSubject* sub = new ConcreteSubject();
	Observer* o1 = new ConcreteObserverA(sub);
	Observer* o2 = new ConcreteObserverB(sub);
	sub->SetState("old");
	sub->Notify();
	sub->SetState("new");//Ҳ������Observer����
	sub->Notify();

	/*result
		ConcreteObserverB observer ...old
		ConcreteObserverA observer ...old
		ConcreteObserverB observer ...new
		ConcreteObserverA observer ...new
	*/

	return 0;
}
