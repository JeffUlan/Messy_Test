#include "extern.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/78941738

extern std::string extern_variable_blog_addr;
extern std::string extern_variable_github_addr;
extern int extern_function_add(int a, int b);
extern const std::string extern_function_name();

namespace extern_ {

namespace {
	int fcn() { return 0; }
}

extern double pi = 3.1415; // ����

/* reference: C++ Primer(Fifth ���İ�) pages 63
ĳЩʱ��������һ��const���������ĳ�ʼֵ����һ���������ʽ������ȷʵ�б�Ҫ���ļ��乲��
��������£����ǲ�ϣ��������Ϊÿ���ļ��ֱ����ɶ����ı������෴��������������const����
������(�ǳ���)����һ��������Ҳ����˵��ֻ��һ���ļ��ж���const��������������ļ�������
��ʹ����������İ취�ǣ�����const�����������������Ƕ��嶼���extern�ؼ��֣�����ֻ�趨��һ�ξͿ�����
*/
extern const int bufsize = fcn();

int test_extern_1()
{
	extern int i; // ����i���Ƕ���i
	int j; // ����������j
	//extern double pi = 3.1415; // ����,�ں������ڲ��������ͼ��ʼ��һ����extern�ؼ��ֱ�ǵı���������������

	return 0;
}

int test_extern_2()
{
	fprintf(stdout, "blob addr: %s\n", extern_variable_blog_addr.c_str());
	fprintf(stdout, "github addr: %s\n", extern_variable_github_addr.c_str());

	fprintf(stdout, "a + b = %d\n", extern_function_add(2, 3));

	fprintf(stdout, "name: %s\n", extern_function_name().c_str());

	return 0;
}

} // namespace extern_

