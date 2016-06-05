#ifndef FBC_MESSY_TEST_FACTORY1_HPP_
#define FBC_MESSY_TEST_FACTORY1_HPP_

typedef enum ProductTypeTag_1
{
	ADD_ = 1,
	SUB_ = 2,
	MUL_ = 3,
	DIV_ = 4
}PRODUCTTYPE_1;

//����
class COperation_1
{
public:
	COperation_1();
	virtual ~COperation_1();
	virtual double GetResult() = 0;

protected:
	double m_numA;
	double m_numB;
};

//�ӷ�
class CAddOperation_1 : public COperation_1
{
public:
	CAddOperation_1(double a, double b);
	virtual ~CAddOperation_1();
	virtual double GetResult();
};

//����
class CSubOperation_1 : public COperation_1
{
public:
	CSubOperation_1(double a, double b);
	virtual ~CSubOperation_1();
	virtual double GetResult();
};

//�˷�
class CMulOperation_1 : public COperation_1
{
public:
	CMulOperation_1(double a, double b);
	virtual ~CMulOperation_1();
	virtual double GetResult();
};

//����
class CDivOperation_1 : public COperation_1
{
public:
	CDivOperation_1(double a, double b);
	virtual ~CDivOperation_1();
	virtual double GetResult();
};

//������
class CCalculatorFactory_1
{
public:
	static COperation_1* CreateOperation(PRODUCTTYPE_1 type, double a, double b);
};

#endif // FBC_MESSY_TEST_FACTORY1_HPP_
