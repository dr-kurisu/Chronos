#pragma once
#include <Core/Base.h>
#include <functional>

namespace chronos {
	class Monitor : public Base {
	public:
		using WindowChangedCallback =
			std::function<void(const WindowInfo&)>;

		Monitor(const MonitorDesc& desc);
		~Monitor();

		void setWindowChangedCallback(
			WindowChangedCallback callback
		);
		WindowInfo getCurrentForeground();
	private:
		UniquePtr<WindowsWatcher> m_windowsWatcher{};
		WindowChangedCallback m_windowChangedCallback;
	};
}