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

	private:
		UniquePtr<Logger> m_logger{};
		UniquePtr<Monitor> m_monitor{};

		bool m_isRunning = true;
	};
}