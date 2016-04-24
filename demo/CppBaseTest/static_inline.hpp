#ifndef FBC_MESSY_TEST_STATIC_INLINE_HPP_
#define FBC_MESSY_TEST_STATIC_INLINE_HPP_

class FastMath {
public:
	int round(float value) { //�����ڲ�����ĺ���Ĭ�Ͼ�����������,Ҳ���Լ� inline �ؼ��֣������Ƕ����
		return (int)(value + (value >= 0 ? 0.5f : -0.5f));
	}

	inline int floor(float value); // ����Ϊ��������
};

int FastMath::floor(float value)
{
	int i = round(value);
	float diff = (float)(value - i);
	return i - (diff < 0);
}

static inline int Ceil(float value)
{
	int i = (int)(value + (value >= 0 ? 0.5f : -0.5f));
	float diff = (float)(i - value);
	return i + (diff < 0);
}

void test_static_inline1();
void test_static_inline2();

#endif // FBC_MESSY_TEST_STATIC_INLINE_HPP_