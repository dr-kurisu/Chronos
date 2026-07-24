#include <Application/Application.h>
#include <Monitor/Monitor.h>
#include <Activity/ActivityManager.h>
#include <Activity/Activity.h>
#include <Core/Logger.h>

chronos::Application::Application(const ApplicationDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.level);

	ChronosLogInfo("Creating ActivityManager...");
	m_acManager = std::make_unique<ActivityManager>(
		ActivityManagerDesc{
			.base = *m_logger,
			.minDuration = std::chrono::seconds{2},
			.storagePath = "CH/Data/chronos.db"
		}
	);

	ChronosLogInfo("Creating Monitor...");
	m_monitor = std::make_unique<Monitor>(MonitorDesc{ *m_logger });
	m_monitor->setWindowChangedCallback(
		[this](const WindowInfo& info)
		{
			m_acManager->onWindowChanged(info);
		}
	);
	
	m_acManager->createCurrentActivity(m_monitor->getCurrentForeground());
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

