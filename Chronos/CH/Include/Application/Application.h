#pragma once
#include <Core/Base.h>
#include <Core/Core.h>


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
		RefPtr<IActivityStorage> m_storage;

		bool m_isRunning = true;
	};
}