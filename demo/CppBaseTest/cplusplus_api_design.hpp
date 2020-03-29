#ifndef FBC_MESSY_TEST_CPLUSPLUS_API_DESIGN_HPP_
#define FBC_MESSY_TEST_CPLUSPLUS_API_DESIGN_HPP_

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace cplusplus_api_design_ {

///////////////////////////////////////////////////////////
// Pimpl���÷���"�Զ���ʱ��"����������ʱ��ӡ��������ʱ��
class AutoTimer {
public:
	explicit AutoTimer(const std::string& name);
	~AutoTimer();

	AutoTimer(const AutoTimer&) = delete;
	AutoTimer& operator=(const AutoTimer&) = delete;

private:
	class Impl; // ˽����Ƕ��
	std::unique_ptr<Impl> impl_;
};

// ����ģʽ
class Singleton {
public:
	static Singleton& GetInstance() // �ȿ��Է��ص������ָ��Ҳ���Է�������,������ָ��ʱ���ͻ�����ɾ���ö��������÷�������
	{
		static Singleton instance;
		return instance;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:
	Singleton() { fprintf(stdout, "constructor\n"); }
	~Singleton() { fprintf(stdout, "destructor\n"); }
};

// ��һ״̬���ģʽ
class Monostate {
public:
	int GetTheAnswer() const { return answer_; }

private:
	static int answer_; // Ҳ���Խ��þ�̬��������Ϊ.cpp�ļ�������ľ�̬������������˽�е��ྲ̬����
};

// ����ģʽ
class IRenderer {
public:
	virtual ~IRenderer() {}
	virtual void Render() = 0;
};

class RendererFactory {
public:
	IRenderer* CreateRenderer(const std::string& type);
};

// ��չ����ģʽ�����������빤���������֧��������ʱ����µ������ࣺ������ά��һ��ӳ�䣬��ӳ�佫�������봴������Ļص�����������
// Ȼ��Ϳ��������µ�������ͨ��һ���µķ���������ʵ��ע���ע����
// ��Ҫע��������ǣ�����������뱣����״̬��Ϣ����ˣ����ǿ��Ҫ����һʱ�̶�ֻ�ܴ���һ������������Ҳ��Ϊ�ζ�����������Ҳ�ǵ�����ԭ��
class RendererFactory2 {
public:
	typedef IRenderer* (*CreateCallback)();
	static void RegisterRenderer(const std::string& type, CreateCallback cb);
	static void UnRegisterRenderer(const std::string& type);
	static IRenderer* CreateRenderer(const std::string& type);

private:
	typedef std::map<std::string, CreateCallback> callback_map_;
	static callback_map_ renderers_;
};

// ����ģʽ������������Original���ǵ��������
class IOriginal {
public:
	virtual void DoSomething(int value) = 0;
};

class Original : public IOriginal {
public:
	void DoSomething(int value) override { fprintf(stdout, "Original::DoSomething\n"); }
};

class Proxy : public IOriginal {
public:
	Proxy() : orig_(new Original()) {}
	~Proxy() { delete orig_; }

	void DoSomething(int value) override { return orig_->DoSomething(value); }

	Proxy(const Proxy&) = delete;
	Proxy& operator=(const Proxy&) = delete;

private:
	Original* orig_;
};

// ������ģʽ
class Rectangle {
public:
	Rectangle() = default;
	~Rectangle() {}

	void setDimensions(float cx, float cy, float w, float h) { fprintf(stdout, "width: %f, height: %f\n", w, h); }
};

class RectangleAdapter {
public:
	RectangleAdapter() : rect_(new Rectangle()) {}
	~RectangleAdapter() { delete rect_; }

	void Set(float x1, float y1, float x2, float y2)
	{
		float w = x2 - x1;
		float h = y2 - y1;
		float cx = w / 2.f + x1;
		float cy = h / 2.f + y1;
		rect_->setDimensions(cx, cy, w, h);
	}

	RectangleAdapter(const RectangleAdapter&) = delete;
	RectangleAdapter& operator=(const RectangleAdapter&) = delete;

private:
	Rectangle* rect_;
};

// ���ģʽ
class Subsystem1 {
public:
	Subsystem1() = default;
	~Subsystem1() {}
	void Operation() { fprintf(stdout, "subsystem1 operation\n"); }
};

class Subsystem2 {
public:
	Subsystem2() = default;
	~Subsystem2() {}
	void Operation() { fprintf(stdout, "subsystem2 operation\n"); }
};

class Facade {
public:
	Facade() : subs1_(new Subsystem1()), subs2_(new Subsystem2()) {}
	~Facade()
	{
		delete subs1_;
		delete subs2_;
	}

	void OperationWrapper()
	{
		subs1_->Operation();
		subs2_->Operation();
	}

	Facade(const Facade&) = delete;
	Facade& operator=(const Facade&) = delete;

private:
	Subsystem1* subs1_;
	Subsystem2* subs2_;
};

// �۲���ģʽ
class SubjectBase; // ��������
class ObserverBase { // ����۲���
public:
	ObserverBase(std::string name, SubjectBase* sub) : name_(name), sub_(sub) {}
	virtual void Update() = 0;

protected:
	std::string name_;
	SubjectBase* sub_;
};

class StockObserver: public ObserverBase { // ����۲��ߣ�����Ʊ��
public:
	StockObserver(std::string name, SubjectBase* sub) : ObserverBase(name, sub) {}
	void Update() override;
};

class NBAObserver : public ObserverBase { // ����۲��ߣ���NBA��
public:
	NBAObserver(std::string name, SubjectBase* sub) : ObserverBase(name, sub) {}
	void Update() override;
};

class SubjectBase { // ��������
public:
	virtual void Attach(ObserverBase* observer) = 0;
	virtual void Notify() = 0;

public:
	std::string action_;
	std::vector<ObserverBase*> observers_;
};


class SecretarySubject : public SubjectBase { // ��������
public:
	void Attach(ObserverBase* ob) { observers_.push_back(ob); }

	void Notify()
	{
		for (auto it = observers_.cbegin(); it != observers_.cend(); ++it) {
			(*it)->Update();
		}
	}
};

int test_api_design_3();
int test_api_design_3_pimpl();
int test_api_design_3_singleton();
int test_api_design_3_monostate();
int test_api_design_3_factory();
int test_api_design_3_factory_expand();
int test_api_design_3_proxy();
int test_api_design_3_adapter();
int test_api_design_3_facade();
int test_api_design_3_observer();

///////////////////////////////////////////////////////////
class Element;

// ������ģʽ: ��ʾһ��������ĳ����ṹ�еĸ�Ԫ�صĲ���. ��ʹ������ڲ��ı��Ԫ�ص����ǰ���¶�����������ЩԪ�ص��²���
// ������ģʽʹ�����������µĲ���: ������ʹ�����������ڸ��Ӷ���ṹ�Ĺ����Ĳ����������. ��������һ���µķ����߼�����һ������ṹ�϶���һ���µĲ���
class Visitor {
public:
	virtual ~Visitor() = default;
	virtual void VisitConcreteElementA(Element* element) = 0;
	virtual void VisitConcreteElementB(Element* element) = 0;

protected:
	Visitor() = default;
};

class ConcreteVisitorA : public Visitor {
public:
	ConcreteVisitorA() = default;
	~ConcreteVisitorA() = default;

	void VisitConcreteElementA(Element* element) override
	{
		fprintf(stdout, "I will visit ConcreteElementA ...\n");
	}

	void VisitConcreteElementB(Element* element) override
	{
		fprintf(stdout, "I will visit ConcreteElementB ...\n");
	}
};

class ConcreteVisitorB : public Visitor
{
public:
	ConcreteVisitorB() = default;
	~ConcreteVisitorB() = default;

	void VisitConcreteElementA(Element* element) override
	{
		fprintf(stdout, "I will visit ConcreteElementA ...\n");
	}

	void VisitConcreteElementB(Element* element) override
	{
		fprintf(stdout, "I will visit ConcreteElementB ...\n");
	}
};

class Element {
public:
	virtual ~Element() = default;
	virtual void Accept(Visitor* visit) = 0;

protected:
	Element() = default;
};

class ConcreteElementA : public Element {
public:
	ConcreteElementA() = default;
	~ConcreteElementA() = default;

	void Accept(Visitor* visit) override
	{
		fprintf(stdout, "visiting ConcreteElementA ...\n");
		visit->VisitConcreteElementA(this);
	}
};

class ConcreteElementB : public Element {
public:
	ConcreteElementB() = default;
	~ConcreteElementB() = default;

	void Accept(Visitor* visit) override
	{
		fprintf(stdout, "visiting ConcreteElementB ...\n");
		visit->VisitConcreteElementB(this);
	}
};

int test_api_design_12_vistor();
int test_api_design_12();

} // cplusplus_api_design_

#endif // FBC_MESSY_TEST_CPLUSPLUS_API_DESIGN_HPP_
