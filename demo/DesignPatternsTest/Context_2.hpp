#ifndef FBC_MESSY_TEST_CONTEXT2_HPP_
#define FBC_MESSY_TEST_CONTEXT2_HPP_

class Strategy_4;
/*
�������Strategyģʽ�Ĺؼ���Ҳ��Strategyģʽ��Templateģʽ�ĸ����������ڡ�
Strategyͨ��"���"(ί��)��ʽʵ���㷨(ʵ��)���칹����Templateģʽ���ȡ���Ǽ̳еķ�ʽ��
������ģʽ������Ҳ�Ǽ̳к��������ʵ�ֽӿ����õķ�ʽ������
*/

class Context_4
{
public:
	Context_4(Strategy_4* stg);
	~Context_4();
	void DoAction();
protected:
private:
	Strategy_4* _stg;
};

#endif // FBC_MESSY_TEST_CONTEXT2_HPP_