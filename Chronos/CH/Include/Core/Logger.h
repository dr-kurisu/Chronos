#pragma once
#include <Core/Core.h>
#include <format>

namespace chronos {
	class Logger final
	{
		disable_copy_and_move(Logger)
	public:
		enum class LogLevel
		{
			Error = 0,
			Warning,
			Info
		};

		explicit Logger(LogLevel level = LogLevel::Error);
		~Logger();
		// void log(LogLevel level, const char* msg);
		template<typename... Args>
		void log(LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
			if (level > m_level) return;
			auto str = std::format(fmt, std::forward<Args>(args)...);
			_log(level, str.c_str());
		}

	private:
		LogLevel m_level = LogLevel::Error;
		void _log(LogLevel level, const char* message);
		const char* logLevelToString(LogLevel level);
	};
}

#define ChronosLog(logger, type, message,...)\
	logger.log((type), message __VA_OPT__(,) __VA_ARGS__);

#define ChronosLogThrow(logger, exception, type, message, ...)\
{\
		ChronosLog(logger, type, message, __VA_ARGS__)\
		throw exception(message);\
}

#define ChronosLogInfo(message,...)\
	ChronosLog(getLogger(), Logger::LogLevel::Info, message, __VA_ARGS__)

#define ChronosLogWarning(message,...)\
	ChronosLog(getLogger(), Logger::LogLevel::Warning, message, __VA_ARGS__)

#define ChronosLogError(message,...)\
	ChronosLog(getLogger(), Logger::LogLevel::Error, message, __VA_ARGS__)

#define ChronosLogThrowError(message,...)\
	ChronosLogThrow(getLogger(), std::runtime_error, Logger::LogLevel::Error, message, __VA_ARGS__)

#define ChronosLogThrowInvalidArg(message,...)\
	ChronosLogThrow(getLogger(), std::invalid_argument, Logger::LogLevel::Error, message, __VA_ARGS__)