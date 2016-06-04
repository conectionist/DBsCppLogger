#include "DBsCppLogger.h"
#include <thread>
#include <iostream>
#include <string>

class Test
{
public:
	template< class CharT, class Traits >
	friend std::basic_ostream<CharT, Traits>&
		operator<<(std::basic_ostream<CharT, Traits>& ost, const Test& t);

	std::string ToString() const
	{
		return "Test class";
	}
};

template< class CharT, class Traits >
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& ost, const Test& t)
{
	ost << t.ToString().c_str();
	return ost;
}

void LogSomeStuff()
{
	DBsCppLogger::InitLogger("log.txt");

	wchar_t* ustr = L"unicode str";
	string s = "an std::string";
	wstring ws = L"an std::wstring";
	double e = 10e40;
	Test t;
	string multilineString =
		"\n{\n\tname : john,\n\tage: 20\n}";

	LOGD << "a debug message";
	LOGI << "a info message";
	LOGW << "a warning message";
	LOGE << "a error message";
	LOGC << "a critical message";
	
	LOGD << "a raw C string";
	LOGD << "some numbers: " << 43 << " " << 1.2 << " " << e << " " << -2 << " " << 11111111111111111l;
	LOGI << "a char* variable: " << ustr;
	
	LOGD << s;
	LOGD << ws;

	LOGD << "A multineline string: " << multilineString;

	LOGD << "the current thread id: " << std::this_thread::get_id();

	LOGD << "An object: " << t;
}