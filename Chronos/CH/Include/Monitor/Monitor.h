#pragma once
#include <Core/Base.h>

namespace chronos {
	class Monitor : public Base {
	public:
		Monitor(const MonitorDesc& desc);
		~Monitor();
	private:
		UniquePtr<WindowsWatcher> m_windowsWatcher{};
	};
}