#include <Application/Application.h>
#include <Monitor/Monitor.h>
#include <Core/Logger.h>

chronos::Application::Application(const ApplicationDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.level);
	m_monitor = std::make_unique<Monitor>(MonitorDesc{ *m_logger });
	ChronosLogInfo("Chronos Lanuched");
}

chronos::Application::~Application()
{
	ChronosLogInfo("Chronos Shutting Down");
}

chronos::Logger& chronos::Application::getLogger() noexcept
{
	return *m_logger;
}

