#pragma once
#include <Core/Common.h>
#include <Core/Base.h>
#include <Windows.h>

namespace chronos {
	class WindowsWatcher : public Base
	{
	public:
		WindowsWatcher(const WindowsWatcherDesc& desc);
		void registerHooks();
		void unregisterHooks();
		WindowInfo getCurrentForeground();
		WindowInfo getWindowInfo(HWND hwnd);
	private:
		static WindowsWatcher* s_instance;

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


