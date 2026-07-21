#pragma once
#include <Core/Common.h>
#include <Core/Base.h>
#include <Windows.h>
#include <functional>

namespace chronos {
	class WindowsWatcher : public Base
	{
	public:
		using WindowChangedCallback =
			std::function<void(const WindowInfo&)>;

		WindowsWatcher(const WindowsWatcherDesc& desc);
		void registerHooks();
		void unregisterHooks();
		WindowInfo getCurrentForeground();
		WindowInfo getWindowInfo(HWND hwnd);
		void setWindowsChangedCallback(WindowChangedCallback callback);
	private:
		static WindowsWatcher* s_instance;
		WindowChangedCallback m_windowChangedCallback;
		HWINEVENTHOOK m_foregroundHook = nullptr;

		static void CALLBACK WinEventProc(
			HWINEVENTHOOK hook,
			DWORD event,
			HWND hwnd,
			LONG idObject,
			LONG idChild,
			DWORD idEventThread,
			DWORD dwmsEventTime);
		void handleForegroundChanged(HWND hwnd);
	};
}


