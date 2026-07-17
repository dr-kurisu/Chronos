#include <Core/Logger.h>
#include <iostream>

chronos::Logger::Logger(LogLevel logLevel)
{
	std::clog << "[Chronos Logger]: Log level set to " << static_cast<int>(logLevel) << "\n";
	std::clog << "-----------------------------------------------------------" << "\n";
}

chronos::Logger::~Logger()
{
}

void chronos::Logger::_log(LogLevel level, const char* message)
{
	auto logLevelToString = [](LogLevel level) {
		switch (level) {
		case LogLevel::Info: return "Info";
		case LogLevel::Warning: return "Warning";
		case LogLevel::Error: return "Error";
		default: return "Unknown";
		}
		};
	if (level > m_logLevel) return;
	std::clog << "[Chronos " << logLevelToString(level) << "]: " << message << "\n";
}

