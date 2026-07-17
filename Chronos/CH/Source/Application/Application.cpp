#include <Application/Application.h>
#include <Core/Logger.h>
#include <iostream>

chronos::Application::Application(const ApplicationDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.level);
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

