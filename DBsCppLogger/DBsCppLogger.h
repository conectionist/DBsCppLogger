#ifndef DBS_CPP_LOGGER
#define DBS_CPP_LOGGER

#include <fstream>
#include <string>
#include <mutex>
#include <sstream>
#include <thread>

using std::wofstream;
using std::string;
using std::wstring;
using std::mutex;
using std::wostringstream;
using std::thread;

#define EXTRA_INFO << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << " : "
#define FUNC_NAME << __FUNCTION__ << " : "

namespace DBsCppLogger
{

#pragma region Logger

	class Logger
	{
	public:
		template<class T>
		Logger& operator<<(const T& data);

		Logger& operator<<(const string& data);

	protected:
		virtual string GetLogLevel() = 0;
		void WriteToLog();

	protected:
		std::wostringstream m_stream;
	};

	template<class T>
	Logger& Logger::operator<<(const T &data)
	{
		m_stream << data;
		return *this;
	}

#pragma endregion

	class log_debug : public Logger
	{
	public:
		~log_debug();

	protected:
		string GetLogLevel();
	};

	class log_info : public Logger
	{
	public:
		~log_info();

	protected:
		string GetLogLevel();
	};

	class log_warning : public Logger
	{
	public:
		~log_warning();

	protected:
		string GetLogLevel();
	};

	class log_error : public Logger
	{
	public:
		~log_error();

	protected:
		string GetLogLevel();
	};

	class log_critical : public Logger
	{
	public:
		~log_critical();

	protected:
		string GetLogLevel();
	};

#pragma region LogWriter

	class LogWriter
	{
	public:
		static LogWriter& getInstance();
		static void SetLogPath(const char* path);
		static void WriteToLog(const wstring& msg, const string& sLogLevel);
		
	private:
		LogWriter()
		{}

		static LogWriter* m_Instance;

	private:
		static wofstream m_fStream;
		static mutex writeMutex;
	};

	void InitLogger(const char* path);

#pragma endregion

#pragma region Utility functions

	string GetCurrentDateTime();
	thread::id GetCurrentThreadId();

#pragma endregion
}

#ifdef ENABLE_SHORT_LOGGER_CLASS_NAMES
	typedef DBsCppLogger::log_debug debug;
	typedef DBsCppLogger::log_info info;
	typedef DBsCppLogger::log_warning warning;
	typedef DBsCppLogger::log_error error;
	typedef DBsCppLogger::log_critical critical;
#endif

#define LOGD DBsCppLogger::log_debug() FUNC_NAME
#define LOGI DBsCppLogger::log_info() FUNC_NAME
#define LOGW DBsCppLogger::log_warning() FUNC_NAME
#define LOGE DBsCppLogger::log_error() FUNC_NAME
#define LOGC DBsCppLogger::log_critical() FUNC_NAME

#endif //DBS_CPP_LOGGER
