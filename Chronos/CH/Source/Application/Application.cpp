#include <Core/All.h>

chronos::Application::Application(const ApplicationDesc& desc)
{
	initialiseLogger(desc);

	initialiseDatabase(desc);

	if (desc.display) 
	{
		createWindow(desc);

		initialiseWebView(desc);
	}

	createStorages();

	createManagers();

	createMonitor();

	createActivitySummary();

	createBackend();
}

chronos::Application::~Application()
{
	ChronosLogInfo("Chronos Shutting Down");
}

chronos::Logger& chronos::Application::getLogger() noexcept
{
	return *m_logger;
}

bool chronos::Application::login(const std::string& username, const std::string& password)
{
	// auto result = m_userManager->login("TestUser", "TestPassword");
	auto result = m_userManager->login(username, password);
	if (!result) 
	{
		ChronosLogWarning("Failed to login test account");
		return false;
	}
	m_acManager->setCurrentUserId(m_userManager->getCurrentUserId());
	m_tagManager->setCurrentUserId(m_userManager->getCurrentUserId());
	m_acSummary->setCurrentUserId(m_userManager->getCurrentUserId());
	// create builtin tags
	m_tagManager->ensureBuiltinTags();
	m_tagManager->updateTagMap();
	m_acManager->updateTagMap(m_tagManager->getTagMap());
	return true;
}

void chronos::Application::logout()
{
	m_userManager->logout();
	m_acManager->setCurrentUserId(static_cast<UserId>(-1));
	m_tagManager->setCurrentUserId(static_cast<UserId>(-1));
	m_acSummary->setCurrentUserId(static_cast<UserId>(-1));
}

void chronos::Application::initialiseLogger(const ApplicationDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.level);
}


void chronos::Application::initialiseDatabase(const ApplicationDesc& desc)
{
	m_db = std::make_shared<SQLiteDatabase>(
		SQLiteDatabaseDesc{
			*m_logger,
			desc.storagePath
		}
	);
	ChronosLogInfo("SQLiteDatabase initialised.");
}

void chronos::Application::initialiseWebView(const ApplicationDesc& desc)
{
	m_webView = std::make_unique<WebViewController>();
	if (!m_webView->initialise(m_window->handle()))
	{
		ChronosLogError("Failed to initialise WebView2.");
	}
}
	
void chronos::Application::createWindow(const ApplicationDesc& desc)
{
	WindowDesc windowDesc{ *m_logger, {1800, 1020} };
	m_window = std::make_unique<Window>(windowDesc);
	m_window->setResizeCallback(
		[this](int width, int height) 
		{
			m_webView->resize(width, height);
		}
	);
}

void chronos::Application::createManagers()
{
	m_userManager = std::make_unique<UserManager>(UserManagerDesc{ *m_logger, *m_userStorage });
	m_acManager = std::make_unique<ActivityManager>(
		ActivityManagerDesc{
			.base = *m_logger,
			.minDuration = std::chrono::seconds{2},
			.storage = *m_acStorage
		}
	);
	m_tagManager = std::make_unique<TagManager>(TagManagerDesc{ *m_logger, *m_tagStorage });
	ChronosLogInfo("Managers initialised.")
}

void chronos::Application::createStorages()
{
	m_acStorage = std::make_unique<SQLiteActivityStorage>(SQLiteStorageDesc{ *m_logger, *m_db });
	m_tagStorage = std::make_unique<SQLiteTagStorage>(SQLiteStorageDesc{ *m_logger, *m_db });
	m_userStorage = std::make_unique<SQLiteUserStorage>(SQLiteStorageDesc{ *m_logger, *m_db });
	m_planStorage = std::make_unique<SQLitePlanStorage>(SQLiteStorageDesc{ *m_logger, *m_db });
	ChronosLogInfo("Storage layer initialised.");
}

void chronos::Application::createMonitor()
{
	m_monitor = std::make_unique<Monitor>(
		MonitorDesc{ *m_logger }
	);
	m_monitor->setWindowChangedCallback(
		[this](const WindowInfo& info)
		{
			m_acManager->onWindowChanged(info);
		}
	);
	ChronosLogInfo("Storage layer initialised.");
}

void chronos::Application::createActivitySummary()
{
	m_summaryGenerator = std::make_unique<RuleBasedSummaryGenerator>();
	m_acSummary = std::make_unique<ActivitySummary>(ActivitySummaryDesc{ 
		*m_logger, *m_acStorage, *m_tagStorage, *m_summaryGenerator 
		});
	ChronosLogInfo("Activity summary service initialised.");
}

void chronos::Application::createBackend()
{
	m_activityController = std::make_unique<ActivityController>(ActivityControllerDesc{ *m_logger, *m_acSummary, *m_acManager });
	m_userController = std::make_unique<UserController>(UserControllerDesc{ *m_logger, *this, *m_userManager });
	m_backend = std::make_unique<Backend>(BackendDesc{
		*m_logger, 
		*m_activityController, 
		*m_userController,
		18080 
	});
}