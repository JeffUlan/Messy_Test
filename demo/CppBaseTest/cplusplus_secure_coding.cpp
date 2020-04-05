#define __STDC_WANT_LIB_EXT1__ 1
#include "cplusplus_secure_coding.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <string>
#include <memory>
#include <iostream>

// reference: ��C��C++��ȫ����(ԭ���2��)��

namespace cplusplus_secure_coding_ {

///////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/105325508

namespace {

void calculate_array_size(int arr1[], char arr3[])
{
	int arr2[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	fprintf(stdout, "arr2 element count: %d\n", sizeof(arr2) / sizeof(arr2[0])); // 8

	// �˴�arr1��һ����������������������ָ�룬��x64�У�sizeof(int*)=8����x86��,sizeof(int*)=4
	// ��������Ϊ���������ᱻC����ת��Ϊָ�룬������sizeof��"����"����Ϊsizeof���Ǻ������������
	// sizeof�������Ӧ��������Ϊ����������͵Ĳ���ʱ���������������(��ָ��)���ʹ�С
	fprintf(stdout, "arr1 element count: %d\n", sizeof(arr1) / sizeof(arr1[0])); // 2, error
	fprintf(stdout, "sizeof(int*): %d\n", sizeof(int*)); // 8 // note: x64, not x86

	fprintf(stdout, "arr3 byte count: %d\n", strlen(arr3)); // 10
}

void string_literal()
{
	const char s1[4] = "abc"; // ���Ƽ�,�κ����������Ϊһ�����ֽڽ�β���ַ�����ʹ�ö��ᵼ��©������Ϊs1û����ȷ���Կ��ַ���β
	const char s2[] = "abc";  // �Ƽ�,����һ�����ַ�������ֵ��ʼ�����ַ�������ָ�����Ľ���,��Ϊ���������Զ�Ϊ�����ַ�������ֵ�����㹻�Ŀռ䣬������ֹ�Ŀ��ַ�
	fprintf(stdout, "s1 length: %d, s2 length: %d\n", strlen(s1), strlen(s2)); // 3, 3
}

void string_size()
{
	wchar_t wide_str1[] = L"0123456789";
	// �������ɿ��ַ�����һ������������ֽ���(������ֹ�ַ�)
	wchar_t* wide_str2 = (wchar_t*)malloc((wcslen(wide_str1) + 1) * sizeof(wchar_t));
	free(wide_str2);
}

int test_secure_coding_2_1()
{
	int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	char arr3[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', '\0' };
	calculate_array_size(arr1, arr3);

	string_literal();

	char x = 'a';
	fprintf(stdout, "sizeof('a'): %d, sizeof(x): %d\n", sizeof('a'), sizeof(x)); // 1, 1

	string_size();

	return 0;
}

void test_unbounded_string_copy()
{
	char buf[12];
	std::cin >> buf; // ����û��������11���ַ����ᵼ��дԽ��
	std::cout << "echo: " << buf << std::endl;

	std::cin.width(12); // ͨ��������Ա����Ϊ�ַ�����ĳ������������
	std::cin >> buf;
	std::cout << "echo: " << buf << std::endl;
}

void test_off_by_one_error()
{
#ifdef _MSC_VER
	char s1[] = "012345678";
	char s2[] = "0123456789";

	strcpy_s(s1, sizeof(s2), s2); // error
	//char* s3 = (char*)malloc(strlen(s2) + 1); // note: when free, it will crash
	char s4[20];
	int r = strcpy_s(s4, _countof(s4), s2); // gcc version > 5.0
	fprintf(stdout, "s4: %s\n", s4);

	//char* dest = (char*)malloc(strlen(s1)); // error
	char* dest = (char*)malloc(strlen(s1) + 1);
	int i = 0;
	//for (i = 1; i <= 11; i++) // error
	for (i = 0; i < strlen(s1); ++i) {
		dest[i] = s1[i];
	}
	dest[i] = '\0';

	fprintf(stdout, "dest: %s\n", dest);
	free(dest);
#endif
}

void test_null_termination_error()
{
	char a[16], b[16], c[16];
	// No null-character is implicitly appended at the end of destination if source is longer than num.
	// Thus, in this case, destination shall not be considered a null terminated C string (reading it as such would overflow)
	//strncpy(a, "0123456789abcdef", sizeof(a)); // error, a��δ�Կ��ַ���β
	//fprintf(stdout, "a: %s\n", a); // a��δ�Կ��ַ���β,�����޷�������ӡa
	strncpy(a, "0123456789abcde", sizeof(a));
	//strncpy(b, "0123456789abcdef", sizeof(b)); // error, b��δ�Կ��ַ���β
	//fprintf(stdout, "b: %s\n", b); // b��δ�Կ��ַ���β,�����޷�������ӡb
	strncpy(b, "0123456789abcde", sizeof(b));
	// To avoid overflows, the size of the array pointed by destination shall be long enough to contain the 
	// same C string as source (including the terminating null character)
	strcpy(c, a); // ��a��δ�Կ��ַ���β,��ôcҲδ�Կ��ַ���β������c����д��ԶԶ������������ޣ������޷�������ӡc
	fprintf(stdout, "a: %s, b: %s, c: %s\n", a, b, c);

	char d[16];
	strncpy(d, "0123456789abcdefghijk", sizeof(d) - 1);
	d[sizeof(d) - 1] = '\0';
	fprintf(stdout, "d: %s\n", d);
}

int test_secure_coding_2_2()
{
	//test_unbounded_string_copy();
	//test_off_by_one_error();
	test_null_termination_error();

	return 0;
}

void test_basic_string()
{
	std::string str;
	std::cin >> str;
	std::cout << "str: " << str << std::endl;

	// ʹ�õ���������һ���ַ���������
	for (std::string::const_iterator it = str.cbegin(); it != str.cend(); ++it) {
		std::cout << *it;
	}
	std::cout << std::endl;
}

void test_string_reference_invalid()
{
	char input[] = "feng;bing;chun;email";
	std::string email;
	std::string::iterator loc = email.begin();
	for (int i = 0; i < strlen(input); ++i) {
		if (input[i] != ';') {
			//email.insert(loc++, input[i]); // �Ƿ�������
			loc = email.insert(loc, input[i]);
		} else {
			//email.insert(loc++, ' '); // �Ƿ�������
			loc = email.insert(loc, ' ');
		}
		++loc;
	}
	fprintf(stdout, "email: %s\n", email.c_str());
}

int test_secure_coding_2_4()
{
	//test_basic_string();
	test_string_reference_invalid();

	return 0;
}

void test_fgets()
{
	char buf[10];

	if (fgets(buf, sizeof(buf), stdin)) {
		// fgets�ɹ���ɨ����һ��з�
		char* p = strchr(buf, '\n');
		if (p) {
			*p = '\0';
		} else {
			// δ�ҵ����з�,ˢ��stdin����β
			int ch;
			while (((ch = getchar()) != '\n') && !feof(stdin) && !ferror(stdin));
		}
	} else { // fgetsʧ��
		fprintf(stderr, "fail to fgets\n");
	}

	fprintf(stdout, "buf: %s\n", buf);
}

void test_getchar()
{
	const int BUFSIZE = 10;
	char buf[BUFSIZE];
	int ch;
	int index = 0;
	int chars_read = 0;

	while (((ch = getchar()) != '\n') && !feof(stdin) && !ferror(stdin)) {
		if (index < BUFSIZE - 1) {
			buf[index++] = (unsigned char)ch;
		}
		++chars_read;
	}

	buf[index] = '\0'; // ���ս��

	if (feof(stdin)) { fprintf(stderr, "EOF\n"); } // ����EOF
	if (ferror(stdin)) { fprintf(stderr, "ERROR\n"); } // �������
	if (chars_read > index) { fprintf(stderr, "truncated\n"); } // ����ض�

	fprintf(stdout, "buf: %s\n", buf);
}

void test_gets_s()
{
#ifdef _MSC_VER
	char buf[10];
	if (gets_s(buf, sizeof(buf)) == NULL) { // �������
		fprintf(stderr, "fail to gets_s\n");
	}

	fprintf(stdout, "buf: %s\n", buf);
#endif
}

void test_strncpy()
{
	char source[] = "http://blog.csdn.net/fengbingchun";
	char* dest = (char*)malloc(sizeof(source) + 1);
	size_t dest_size = strlen(dest);
	strncpy(dest, source, dest_size - 1);
	dest[dest_size - 1] = '\0';
	fprintf(stdout, "dest: %s\n", dest);
	free(dest);
}

void test_strncpy_s()
{
#ifdef _MSC_VER
	char src1[100] = "hello";
	char src2[7] = { 'g', 'o', 'o', 'd', 'b', 'y', 'e' };
	char dst1[6], dst2[5], dst3[5];
	errno_t r1, r2, r3;

	r1 = strncpy_s(dst1, sizeof(dst1), src1, sizeof(src1));
	fprintf(stdout, "dst1: %s, r1: %d\n", dst1, r1); // hello\0
	r2 = strncpy_s(dst2, sizeof(dst2), src2, 4);
	fprintf(stdout, "dst2: %s, r2: %d\n", dst2, r2); // good\0
	//r3 = strncpy_s(dst3, sizeof(dst3), src1, sizeof(src1)); // crash, r3��û�з��ط���ֵ��ԭ��Ӧ����û�п�������ʱԼ��
	//fprintf(stdout, "dst3: %s, r3: %d\n", dst3, r3);
#endif
}

int test_secure_coding_2_5()
{
	//test_fgets();
	//test_getchar();
	//test_gets_s();
	//test_strncpy();
	test_strncpy_s();

	return 0;
}

} // namespace

int test_secure_coding_2()
{
	//return test_secure_coding_2_1();
	//return test_secure_coding_2_2();
	//return test_secure_coding_2_4();
	return test_secure_coding_2_5();
}

///////////////////////////////////////////////////////////
int test_secure_coding_3()
{
	return 0;
}

///////////////////////////////////////////////////////////
int test_secure_coding_4()
{
	return 0;
}

///////////////////////////////////////////////////////////
int test_secure_coding_5()
{
	return 0;
}

///////////////////////////////////////////////////////////
int test_secure_coding_6()
{
	return 0;
}

///////////////////////////////////////////////////////////
int test_secure_coding_7()
{
	return 0;
}

///////////////////////////////////////////////////////////
int test_secure_coding_8()
{
	return 0;
}

///////////////////////////////////////////////////////////
int test_secure_coding_9()
{
	return 0;
}

} // namespace cplusplus_secure_coding_
