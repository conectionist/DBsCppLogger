#include "DBsCppLogger.h"

#include <windows.h>
#include <thread>

using std::thread;

void log_stuff()
{
	for (int i = 0; i < 10; i++)
	{
		LOGD << "logging some stuff: " << i << " " << "john";
		LOGI << L"some informative stuff " << i + 1;

		Sleep(200);
	}
}

void LogSomeStuff()
{
	DBsCppLogger::InitLogger("log.txt");

	thread t1(log_stuff);
	thread t2(log_stuff);

	t1.join();
	t2.join();
}