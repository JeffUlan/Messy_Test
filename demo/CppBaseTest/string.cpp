#include "string.hpp"
#include <string>
#include <iostream>
#include <cctype>

/*
	typedef basic_string<char, char_traits<char>, allocator<char> >			string;
	typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >	wstring;
	typedef basic_string<char16_t, char_traits<char16_t>, allocator<char16_t> >	u16string;
	typedef basic_string<char32_t, char_traits<char32_t>, allocator<char32_t> >	u32string;
*/

// reference: http://www.cplusplus.com/reference/string/string/
int test_string_func()
{
	{ // append
		std::string str;
		std::string str2 = "Writing ";
		std::string str3 = "print 10 and then 5 more";

		// used in the same order as described above:
		str.append(str2);                       // "Writing "
		str.append(str3, 6, 3);                   // "10 "
		str.append("dots are cool", 5);          // "dots "
		str.append("here: ");                   // "here: "
		str.append(10u, '.');                    // ".........."
		str.append(str3.begin() + 8, str3.end());  // " and then 5 more"
		str.append(5, 0x2E);                // "....."

		std::cout << str << '\n';
	}

	{ // assign
		std::string str;
		std::string base = "The quick brown fox jumps over a lazy dog.";

		// used in the same order as described above:
		str.assign(base);
		std::cout << str << '\n';

		str.assign(base, 10, 9);
		std::cout << str << '\n';         // "brown fox"

		str.assign("pangrams are cool", 7);
		std::cout << str << '\n';         // "pangram"

		str.assign("c-string");
		std::cout << str << '\n';         // "c-string"

		str.assign(10, '*');
		std::cout << str << '\n';         // "**********"

		str.assign(10, 0x2D);
		std::cout << str << '\n';         // "----------"

		str.assign(base.begin() + 16, base.end() - 12);
		std::cout << str << '\n';         // "fox jumps over"
	}

	{ // at
		std::string str("Test string");
		for (unsigned i = 0; i<str.length(); ++i) {
			std::cout << str.at(i);
		}
		std::cout << '\n';
	}

	{ // back
		std::string str("hello world.");
		str.back() = '!';
		std::cout << str << '\n';
	}

	{ // begin/end
		std::string str("Test string");
		for (std::string::iterator it = str.begin(); it != str.end(); ++it)
			std::cout << *it;
		std::cout << '\n';
	}

	{ // capacity
		std::string str("Test string");
		std::cout << "size: " << str.size() << "\n";
		std::cout << "length: " << str.length() << "\n";
		std::cout << "capacity: " << str.capacity() << "\n";
		std::cout << "max_size: " << str.max_size() << "\n";
	}

	{ // cbegin/cend
		std::string str("Lorem ipsum");
		for (auto it = str.cbegin(); it != str.cend(); ++it)
			std::cout << *it;
		std::cout << '\n';
	}

	{ // clear
		char c;
		std::string str;
		std::cout << "Please type some lines of text. Enter a dot (.) to finish:\n";
		do {
			c = std::cin.get();
			str += c;
			if (c == '\n') {
				std::cout << str;
				str.clear();
			}
		} while (c != '.');
	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	{ //

	}

	return 0;
}

int test_string_init()
{
	// ���ʹ�õȺ�(=)��ʼ��һ��������ʵ����ִ�е��ǿ�����ʼ�����������ѵȺ��Ҳ�ĳ�ʼ���������´����Ķ�����ȥ��
	// ��֮�෴�������ʹ�õȺţ���ִ�е���ֱ�ӳ�ʼ��
	std::string s1; // Ĭ�ϳ�ʼ����s1��һ���մ�
	std::string s2(s1); // s2��s1�ĸ���
	std::string s3 = s1; // �ȼ���s3(s1)��s3��s1�ĸ���
	std::string s4("value"); // s4������ֵ"value"�ĸ�������������ֵ�����Ǹ����ַ��⣬ֱ�ӳ�ʼ��
	std::string s5 = "value"; // �ȼ���s5("value"),s5������ֵ"value"�ĸ���,������ʼ��
	std::string s6(10, 'c'); // ��s6��ʼ��Ϊ������10���ַ�c��ɵĴ���ֱ�ӳ�ʼ��
	// �����ö��ֵ���г�ʼ�����������Ҫ�ÿ�����ʼ���ķ�ʽ������Ҳ���ǲ����ԣ�
	// ������Ҫ��ʾ�ش���һ��(��ʱ)�������ڿ���
	std::string s7 = std::string(10, 'c'); // ������ʼ�����ȼ��ڣ� std::string tmp(10, 'c'); std::string s7 = tmp;
	// string s(s2, pos2) : s��string s2���±�pos2��ʼ���ַ��Ŀ�������pos2>s2.size()�����캯������Ϊδ����
	std::string s8(s4, 2);
	// string s(cp, n) : s��cpָ���������ǰn���ַ��Ŀ���������������Ӧ�ð���n���ַ�
	char cp[6] {"abcde"};
	std::string s9(cp, 2);
	// string s(s2, pos2, len2) : s��string s2���±�pos2��ʼlen2���ַ��Ŀ�������pos2>s2.size(),���캯������Ϊδ����.
	// ����len2��ֵ�Ƕ��٣����캯�����࿽��s2.size()-pos2���ַ�
	std::string s10(s4, 1, 2);

	return 0;
}

int test_string_base()
{
	int num{ 0 };
	std::cin >> num;

	switch (num) {
	case 0: {
		// ��дstring����
		std::string s1;
		std::cin >> s1; // ��string�������s1,�����հ�ֹͣ, string������Զ���Ȼ��ͷ�Ŀհ�(���ո�������з����Ʊ����)
				// ���ӵ�һ���������ַ���ʼ����ֱ��������һ���հ�Ϊֹ
		std::cout << s1 << std::endl; // ���s1;

		std::string s2, s3;
		std::cin >> s2 >> s3; // �������������������д��һ��
		std::cout << s2 << s3 << std::endl;
	}
	break;
	case 1: {
		// ��ȡδ֪������string����
		std::string s4;
		while (std::cin >> s4) { // ������ȡ��ֱ�������ļ�ĩβ(ctrl+z)
			std::cout << s4 << std::endl; // ���������ʣ�ÿ�����ʺ������һ������
		}
	}
	break;
	case 2: {
		// ʹ��getline��ȡһ����,getlineֻҪһ�������з��ͽ�����ȡ���������ؽ��
		std::string s5;
		while (std::getline(std::cin, s5)) { // ��ctrl+z�˳�ѭ��
			std::cout << s5 << std::endl; // ����getline�������ص��Ǹ����з�ʵ���ϱ��������ˣ�
						      // �õ���string�����в��������û��з�
		}
	}
	break;
	case 3: {
		// empty���Ƿ�Ϊ�շ���һ����Ӧ�Ĳ���ֵ
		// ÿ�ζ���һ���У���������ֱ������
		std::string s6;
		while (std::getline(std::cin, s6)) {
			if (!s6.empty())
				std::cout << s6 << std::endl;
			else
				std::cout << "it is empty" << std::endl;
		}
	}
	break;
	case 4: {
		// size�� ����string����ĳ���(��string�������ַ��ĸ���)
		std::string s7;
		while (std::getline(std::cin, s7)) {
			auto len = s7.size(); // size�������ص���һ��std::string::size_type���͵�ֵ��
					      // ����һ���޷������͵�ֵ���������㹻������κ�string����Ĵ�С,
			std::cout << "string size: " << len << std::endl;
		}
	}
	break;
	case 5: {
		// �Ƚ�string���󣺴�Сд���У�==��!=��<��<=��>��>=
		std::string s1{ "hello" }, s2{ "Hello" }, s3{"Hello world"};
		if (s1 > s2)
			std::cout << "s1 > s2" << std::endl;
		else if (s1 == s2)
			std::cout << "s1 == s2" << std::endl;
		else if (s1 < s2)
			std::cout << "s1 < s2" << std::endl;

		if (s2 <= s3)
			std::cout << "s2 <= s3" << std::endl;

	}
	break;
	case 6: {
		// +: �������ǰ���������������Ҳ��������󴮽�
		std::string s1{ "hello, " }, s2{ "world" }, s3;
		s3 = s1 + s2;
		std::cout << "s3: " << s3 << std::endl;

		// ����string������ַ�����ֵ���ַ�������ֵ����һ�������ʹ��ʱ��
		// ����ȷ��ÿ���ӷ������(+)������Ķ���������һ����string,
		// ���ܰ�����ֱֵ�����
		// Note: �ַ�������ֵ��string�ǲ�ͬ������
		std::string s4{ "csdn blog" }, s5{ "http://blog.csdn.net/" }, s6;
		s6 = s4 + ": " + s5 + "fengbingchun";
		std::cout << s6 << std::endl;
	}
	break;
	case 7: {
		// substr: ����һ��string������ԭʼstring��һ���ֻ�ȫ���Ŀ���,
		// ���Դ��ݸ�substrһ����ѡ�Ŀ�ʼλ�úͼ���ֵ
		std::string s{ "hello world" };
		std::string s2 = s.substr(0, 5); // s2 = hello
		std::string s3 = s.substr(6); // s3 = world
		std::string s4 = s.substr(6, 11); // s3 = world
		//std::string s5 = s.substr(12); // �׳�һ��out_of_range�쳣
		fprintf(stderr, "s2: %s; s3: %s; s4: %s\n", s2.c_str(), s3.c_str(), s4.c_str());

		// insert��erase��assign
		s.insert(s.size(), 5, '!'); // ��sĩβ����5����̾��
		fprintf(stdout, "s:  %s\n", s.c_str());
		s.erase(s.size() - 5, 5); // ��sɾ�����5���ַ�
		fprintf(stdout, "s: %s\n", s.c_str());

		const char* cp = "Stately, plump Buck";
		s.assign(cp, 7); // s = "Stately"
		fprintf(stdout, "s: %s\n", s.c_str());
		s.insert(s.size(), cp + 7); // s = "Stately, plump Buck"
		fprintf(stdout, "s: %s\n", s.c_str());

		std::string s5{ " some string " }, s6{ " some other string " };
		s5.insert(0, s6); // ��s5��λ��0֮ǰ����s6�Ŀ���
		fprintf(stdout, "s5: %s\n", s5.c_str());
		s5.insert(0, s6, 0, s6.size()); // ��s5[0]֮ǰ����s6��s6[0]��ʼ��s6.size()���ַ�
		fprintf(stdout, "s5: %s\n", s5.c_str());

		// append: ����ĩβ���в��������һ�ּ�д��ʽ
		std::string s7{ "C++ Primer" }, s8{ s7 };
		s7.insert(s7.size(), " 5th Ed.");
		s8.append(" 5th Ed.");
		fprintf(stdout, "s7: %s; s8: %s\n", s7.c_str(), s8.c_str());

		// replace: �ǵ���erase��insert��һ�ּ�д��ʽ
		s7.replace(11, 3, "Fifth"); // s7.erase(11, 3); s7.insert(11, "Fifth");
		fprintf(stdout, "s7: %s\n", s7.c_str());

		/*
			s.find(args)������s��args��һ�γ��ֵ�λ��
			s.rfind(args)������s��args���һ�γ��ֵ�λ��
			s.find_first_of(args)����s�в���args���κ�һ���ַ���һ�γ��ֵ�λ��
			s.find_last_of(args)����s�в���args���κ�һ���ַ����һ�γ��ֵ�λ��
			s.find_first_not_of(args)����s�в��ҵ�һ������args�е��ַ�
			s.find_last_not_of(args)����s�в������һ������args�е��ַ�
		*/
		
		// find: ���ص�һ��ƥ��λ�õ��±�
		std::string s9{ "AnnaBelle" };
		auto pos1 = s9.find("Belle");
		auto pos2 = s9.find("xxx");
		fprintf(stdout, "pos1: %d, pos2: %d\n", pos1, pos2); // 4, -1

		// find_first_of: ����������ַ������κ�һ���ַ�ƥ���λ��
		std::string numbers{ "0123456789" }, name{ "r2d2" };
		auto pos3 = name.find_first_of(numbers);
		fprintf(stdout, "pos3: %d\n", pos3); // 1, name�е�һ�����ֵ��±�

		// find_first_not_of: ��һ�����ڲ����е��ַ�
		std::string s10{ "03714p3" };
		auto pos4 = s10.find_first_not_of(numbers);
		fprintf(stdout, "pos4: %d\n", pos4); // 5

		// compare: ����0(����)������(����)����(С��)
		auto ret = numbers.compare(name);
		fprintf(stdout, "compare result: %d\n", ret);// -1

		// ��ֵ������string֮���ת��
		int i{ 43 };
		std::string s11 = std::to_string(i); // ������iת��Ϊ�ַ���ʾ��ʽ
		double d = std::stod(s11); // ���ַ���s11ת��Ϊ������
		fprintf(stdout, "s11: %s, d: %f\n", s11.c_str(), d);

		/*
			to_string(val):һ�����غ�����������ֵval��string��ʾ��val�������κ���������
			stoi(s,p,b)/stol(s,p,b)/stoul(s,p,b)/stoll(s,p,b)/stoull(s,p,b)������s����ʼ�Ӵ�(��ʾ��������)����ֵ��
				�������ͷֱ���int��long��unsigned long��long long��unsigned long long��b��ʾת�����õĻ�����
				Ĭ��ֵΪ10.p��size_tָ�룬��������s�е�һ������ֵ�ַ����±꣬pĬ����0�����������������±ꡣ
			stof(s,p)/stod(s,p)/stold(s,p)������s����ʼ�Ӵ�(��ʾ����������)����ֵ������ֵ���ͷֱ���float��double��
				long double.����p������������ת��������һ����
		*/
	}
	break;
	default:
		break;
	}
	
	return 0;
}

int test_string_cctype()
{
	/* include <cctype>
		isalnum(c)����c����ĸ������ʱΪ��
		isalpha(c)����c����ĸʱΪ��
		isblank(c)����c�ǿհ��ַ�ʱΪ��(C++11)
		iscntrl(c)����cʱ�����ַ�ʱΪ��
		isdigit(c)����c������ʱΪ��
		isgraph(c)����c���ǿո񵫿ɴ�ӡʱΪ��
		islower(c)����c��Сд��ĸʱΪ��
		isprint(c)����c�ǿɴ�ӡ�ַ�ʱΪ��(��c�ǿո��c���п�����ʽ)
		ispunct(c)����c�Ǳ�����ʱΪ��(��c���ǿ����ַ������֡���ĸ���ɴ�ӡ�հ��е�һ��)
		isspace(c)����c�ǿհ�ʱΪ��(��c�ǿո񡢺����Ʊ���������Ʊ�����س��������з�����ֽ���е�һ��)
		isupper(c)����c�Ǵ�д��ĸʱΪ��
		isxdigit(c)����c��ʮ����������ʱΪ��
		tolower(c)�����c�Ǵ�д��ĸ�������Ӧ��Сд��ĸ������ԭ�����c
		toupper(c)�����c��Сд��ĸ�������Ӧ�Ĵ�д��ĸ������ԭ�����c
	*/

	std::string s1{ "Hello World!!!" };

	decltype(s1.size()) punct_cnt{ 0 };
	for (auto c : s1) {
		if (ispunct(c))
			++punct_cnt;
	}
	std::cout << punct_cnt << " punctutation characters in " << s1 << std::endl;

	for (auto &c : s1) { // ����s1�е�ÿ���ַ�(Note:c������)
		c = toupper(c); // c��һ�����ã���˸�ֵ��佫�ı�s���ַ���ֵ
	}
	std::cout << "toupper s1: " << s1 << std::endl;

	// string������±������ڵ���0��С��s.size()
	// Note��C++��׼����Ҫ���׼�����±��Ƿ�Ϸ���һ��ʹ����һ��������Χ���±꣬�ͻ��������Ԥ֪�Ľ��
	std::string s2{"some string"};
	for (decltype(s2.size()) index = 0; index != s2.size() && !isspace(s2[index]); ++index) {
		s2[index] = toupper(s2[index]);
	}
	std::cout << "s2: " << s2 << std::endl;

	// ʹ���±�ִ���������
	const std::string s3{"0123456789ABCDEF"};
	std::cout << "Enter a series of numbers between 0 and 15"
		<< "separated by spaces. Hit ENTER when finished: " << std::endl;
	std::string result;
	std::string::size_type n;
	while (std::cin >> n) {
		if (n < s3.size())
			result += s3[n];

		std::cout << "Your hex number is: " << result << std::endl;
	}

	return 0;
}


