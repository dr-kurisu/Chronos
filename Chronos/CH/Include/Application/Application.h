#pragma once
#include <Core/Base.h>
#include <Core/Core.h>
#include <sqlite3.h>

namespace chronos {
	class Application {
		disable_copy_and_move(Application)
	public:
		explicit Application(const ApplicationDesc& desc);
		~Application();
		Logger& getLogger() noexcept;
		void run();

	private:
		void login();
		void initialiseLogger(const ApplicationDesc& desc);
		void initialiseDatabase(const ApplicationDesc& desc);
		void initialiseWebView(const ApplicationDesc& desc);
		void createWindow(const ApplicationDesc& desc);
		void createManagers();
		void createStorages();
		void createMonitor();
		void createActivitySummary();
		void createBackend();

	private:
		UniquePtr<Logger> m_logger{};
		UniquePtr<Monitor> m_monitor{};
		UniquePtr<ActivityManager> m_acManager{};
		UniquePtr<UserManager> m_userManager{};
		UniquePtr<TagManager> m_tagManager{};
		UniquePtr<ActivitySummary> m_acSummary{};
		UniquePtr<ISummaryGenerator> m_summaryGenerator{};

		RefPtr<SQLiteDatabase> m_db{};
		UniquePtr<IActivityStorage> m_acStorage{};
		UniquePtr<ITagStorage> m_tagStorage{};
		UniquePtr<IUserStorage> m_userStorage{};
		UniquePtr<IPlanStorage> m_planStorage{};

		UniquePtr<Window> m_window{};
		UniquePtr<WebViewController> m_webView{};
		UniquePtr<Backend> m_backend{};
		UniquePtr<ActivityController> m_activityController{};
		UniquePtr<UserController> m_userController{};

		bool m_isRunning = true;
	};
}