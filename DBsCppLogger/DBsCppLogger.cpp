#include "DBsCppLogger.h"

#include <ctime>
#include <locale>
#include <codecvt>

namespace DBsCppLogger
{
#pragma region Logger

	void Logger::WriteToLog()
	{
		LogWriter::getInstance().WriteToLog(m_stream.str(), GetLogLevel());
	}

#pragma endregion

#pragma region log classes

	log_debug::~log_debug()
	{
		WriteToLog();
	}

	string log_debug::GetLogLevel()
	{
		return "D";
	}

	log_info::~log_info()
	{
		WriteToLog();
	}

	string log_info::GetLogLevel()
	{
		return "I";
	}

	log_warning::~log_warning()
	{
		WriteToLog();
	}

	string log_warning::GetLogLevel()
	{
		return "W";
	}

	log_error::~log_error()
	{
		WriteToLog();
	}

	string log_error::GetLogLevel()
	{
		return "E";
	}

	log_critical::~log_critical()
	{
		WriteToLog();
	}

	string log_critical::GetLogLevel()
	{
		return "C";
	}

#pragma endregion

#pragma region LogWriter

	LogWriter* LogWriter::m_Instance = nullptr;
	wofstream LogWriter::m_fStream;
	mutex LogWriter::writeMutex;

	LogWriter& LogWriter::getInstance()
	{
		if (!m_Instance)
			m_Instance = new LogWriter();

		return *m_Instance;
	}

	void LogWriter::SetLogPath(const char* path)
	{
		m_fStream.open(path, std::ios::app);

		const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
		m_fStream.imbue(utf8_locale);
	}

	void LogWriter::WriteToLog(const wstring& msg, const string& sLogLevel)
	{
		writeMutex.lock();

		m_fStream
			<< GetCurrentDateTime().c_str() << " - "
			<< "Thread " << GetCurrentThreadId() << " - "
			<< sLogLevel.c_str() << " - "
			<< msg << std::endl;

		writeMutex.unlock();
	}

	void InitLogger(const char* path)
	{
		LogWriter::SetLogPath(path);
	}

#pragma endregion

#pragma region Utility functions

	string GetCurrentDateTime()
	{
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		string sTime = "";

		if (tm.tm_mday < 10)
			sTime += std::to_string(0);
		sTime += std::to_string(tm.tm_mday); sTime += ".";

		if (tm.tm_mon + 1 < 10)
			sTime += std::to_string(0);
		sTime += std::to_string(tm.tm_mon + 1); sTime += ".";

		sTime += std::to_string(1900 + tm.tm_year); sTime += " ";

		if (tm.tm_hour < 10)
			sTime += std::to_string(0);
		sTime += std::to_string(tm.tm_hour); sTime += ":";

		if (tm.tm_min < 10)
			sTime += std::to_string(0);
		sTime += std::to_string(tm.tm_min); sTime += ":";

		if (tm.tm_sec < 10)
			sTime += std::to_string(0);
		sTime += std::to_string(tm.tm_sec);

		return sTime;
	}

	std::thread::id GetCurrentThreadId()
	{
		return std::this_thread::get_id();
	}

#pragma endregion
}