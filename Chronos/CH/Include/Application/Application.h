#pragma once
#include <Core/Base.h>
#include <Core/Core.h>
#include <sqlite3.h>


namespace chronos {
	class Application {
		disable_copy_and_move(Application)
	public:
		explicit Application(const ApplicationDesc& desc);
		virtual ~Application();
		virtual Logger& getLogger() noexcept final;
		virtual void run() final;
		virtual void login();

	private:
		UniquePtr<Logger> m_logger{};
		UniquePtr<Monitor> m_monitor{};
		UniquePtr<ActivityManager> m_acManager{};
		UniquePtr<UserManager> m_userManager{};
		UniquePtr<ActivitySummary> m_acSummary{};
		UniquePtr<ISummaryGenerator> m_summaryGenerator{};

		UniquePtr<IActivityStorage> m_acStorage;
		UniquePtr<ITagStorage> m_tagStorage;
		UniquePtr<IUserStorage> m_userStorage;
		UniquePtr<IPlanStorage> m_planStorage;
		RefPtr<SQLiteDatabase> m_db;

		bool m_isRunning = true;
	};
}