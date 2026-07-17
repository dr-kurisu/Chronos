#include <Core/Logger.h>
#include <iostream>

chronos::Logger::Logger(LogLevel level) : m_level(level)
{
	std::clog << "[Chronos Logger]: Log level set to " << chronos::Logger::logLevelToString(level) << "\n";
	std::clog << "-----------------------------------------------------------" << "\n";
}

chronos::Logger::~Logger()
{
}

void chronos::Logger::_log(LogLevel level, const char* message)
{
	if (level > m_level) return;
	std::clog << "[Chronos " << chronos::Logger::logLevelToString(level) << "]: " << message << "\n";
}

const char* chronos::Logger::logLevelToString(LogLevel level)
{
	switch (level) {
	case LogLevel::Info: return "Info";
	case LogLevel::Warning: return "Warning";
	case LogLevel::Error: return "Error";
	default: return "Unknown";
	}
}

