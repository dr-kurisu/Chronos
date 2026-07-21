#include <Application/Application.h>
#include <Monitor/Monitor.h>
#include <Activity/ActivityManager.h>
#include <Core/Logger.h>

chronos::Application::Application(const ApplicationDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.level);

	m_acManager = std::make_unique<ActivityManager>(ActivityManagerDesc{ *m_logger });
	m_monitor = std::make_unique<Monitor>(MonitorDesc{ *m_logger });
	m_monitor->setWindowChangedCallback(
		[this](const WindowInfo& info)
		{
			m_acManager->endCurrentActivity();
			m_acManager->printCurrentActivity();
			m_acManager->createCurrentActivity(info);
		}
	);
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

