#include <Core/Logger.h>
#include <iostream>
#include <sstream>

chronos::Logger::Logger(LogLevel level) : m_level(level)
{
	//std::clog << "[Chronos Logger]: Log level set to " << chronos::Logger::logLevelToString(level) << "\n";
	//std::clog << "-----------------------------------------------------------" << "\n";
}

chronos::Logger::~Logger()
{
}

void chronos::Logger::_log(LogLevel level, const char* message)
{
    std::string prefix =
        std::format("[Chronos {}]: ", logLevelToString(level));

    std::istringstream iss(message);
    std::string line;

    bool first = true;
    while (std::getline(iss, line))
    {
        // deal with first line
        if (first)
        {
            std::clog << prefix << line << '\n';
            first = false;
        }
        // Add indentation with other lines
        else
        {
            std::clog << std::string(prefix.size(), ' ') << line << '\n';
        }
    }
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