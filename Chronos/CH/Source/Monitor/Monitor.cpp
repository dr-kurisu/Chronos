#include <Monitor/Monitor.h>
#include <Monitor/Windows/WindowsWatcher.h>
#include <Activity/Activity.h>

chronos::Monitor::Monitor(const MonitorDesc& desc) : Base(desc.base)
{
	m_windowsWatcher = std::make_unique<WindowsWatcher>(WindowsWatcherDesc{ m_logger , 1.0f });
	m_windowsWatcher->registerHooks();
}

chronos::Monitor::~Monitor()
{
	m_windowsWatcher->unregisterHooks();
}

