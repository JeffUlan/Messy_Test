#include "Composite.hpp"
#include "Component.hpp"
#include "Leaf.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/29401213

Composite_1::Composite_1()
{
	//vector<Component*>::iterator itend = comVec.begin();
}

Composite_1::~Composite_1()
{

}

void Composite_1::Operation()
{
	std::vector<Component_1*>::iterator comIter = comVec.begin();

	for (; comIter != comVec.end(); comIter++)
		(*comIter)->Operation();
}

void Composite_1::Add(Component_1* com)
{
	comVec.push_back(com);
}

void Composite_1::Remove(Component_1* com)
{
	//comVec.erase(&com);
}

Component_1* Composite_1::GetChild(int index)
{
	return comVec[index];
}

int test_Composite1()
{
	Composite* p = new Composite("С��");
	p->Add(new Leaf("С��"));
	p->Add(new Leaf("С��"));

	Composite* p1 = new Composite("СС��");
	p1->Add(new Leaf("����"));

	p->Add(p1);
	p->Display(1);

	/*result
		-С��
		---С��
		---С��
		---СС��
		-----����
	*/

	return 0;
}

int test_Composite2()
{
	ConcreteCompany* p = new ConcreteCompany("�廪��ѧ");
	p->Add(new HrDepartment("�廪��ѧ�˲Ų�"));

	ConcreteCompany* p1 = new ConcreteCompany("��ѧϵ");;
	p1->Add(new HrDepartment("��ѧϵ�˲Ų�"));

	ConcreteCompany* p2 = new ConcreteCompany("����ϵ");
	p2->Add(new HrDepartment("����ϵ�˲Ų�"));

	p->Add(p1);
	p->Add(p2);

	p->Display(1);
	p->LineOfDuty();

	/*result
		-�廪��ѧ
		--�廪��ѧ�˲Ų�
		--��ѧϵ
		---��ѧϵ�˲Ų�
		--����ϵ
		---����ϵ�˲Ų�
		�廪��ѧ�˲Ų�����Ƹ�˲�
		��ѧϵ�˲Ų�����Ƹ�˲�
		����ϵ�˲Ų�����Ƹ�˲�
	*/

	return 0;
}

int test_Composite3()
{
	Leaf_1* l = new Leaf_1();
	l->Operation();

	Composite_1* com = new Composite_1();
	com->Add(l);
	com->Operation();

	Component_1* ll = com->GetChild(0);
	ll->Operation();

	/*result
		Leaf Operation ...
		Leaf Operation ...
		Leaf Operation ...
	*/

	return 0;
}
