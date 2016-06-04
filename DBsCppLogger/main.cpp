#include <iostream>

#define ENABLE_SHORT_LOGGER_CLASS_NAMES

#include "DBsCppLogger.h"

#include <windows.h>
#include <thread>

using namespace std;

void log_stuff()
{
	for (int i : {1, 2, 3, 4, 5, 6, 7, 8, 9})
	{
		debug() << "logging some stuff: " << i << " " << "john";
		info() << L"some informative stuff " << i + 1;

		Sleep(200);
	}
}

int main()
{
	DBsCppLogger::InitLogger("log.txt");

	//thread t1(log_stuff);
	//thread t2(log_stuff);

	//t1.join();
	//t2.join();

	wchar_t* ustr = L"unicode str";

	debug() << "logging some stuff: " << 1 << " " << 2 << " " << "john";
	debug() FUNC_NAME << "some debugging stuff " << 43;
	info() FUNC_NAME << "some info stuff " << ustr;
	warning() FUNC_NAME << "some warning stuff " << 5.8f;
	error() FUNC_NAME << "some error stuff " << 2.5 << L" a unicode string";
	critical() FUNC_NAME << "some critical stuff " << 11111111111111111l;
	warning() FUNC_NAME << "some extra info";

	return 0;
}