#include <Core/All.h>

chronos::Application::Application(const ApplicationDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.level);
	m_storage = std::make_shared<SQLiteActivityStorage>(SQLiteACStorageDesc{ *m_logger, desc.storagePath });

	ChronosLogInfo("Creating UserManager...");
	m_userManager = std::make_unique<UserManager>(UserManagerDesc{*m_logger, *m_storage});

	ChronosLogInfo("Creating ActivityManager...");
	m_acManager = std::make_unique<ActivityManager>(
		ActivityManagerDesc{
			.base = *m_logger,
			.minDuration = std::chrono::seconds{2},
			.storage = *m_storage
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

	ChronosLogInfo("Creating AC Summary...");
	m_summaryGenerator = std::make_unique<RuleBasedSummaryGenerator>();
	m_acSummary = std::make_unique<ActivitySummary>(ActivitySummaryDesc{ *m_logger, *m_summaryGenerator });

	// Login default account
	login();
	// Get current AC
	m_acManager->createCurrentActivity(m_monitor->getCurrentForeground());
	ChronosLogInfo("Chronos Lanuched");
	ChronosLogInfo("------------------------------------------");
}

chronos::Application::~Application()
{
	ChronosLogInfo("Chronos Shutting Down");
}

chronos::Logger& chronos::Application::getLogger() noexcept
{
	return *m_logger;
}

void chronos::Application::login()
{
	auto result = m_userManager->login("TestUser", "TestPassword");
	if (!result) 
	{
		ChronosLogWarning("Failed to login test account");
		return;
	}
	m_acManager->setCurrentUserId(m_userManager->getCurrentUserId());
	ChronosLogInfo("Successfully login to test account");
}
