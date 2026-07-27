#include <Monitor/Windows/WindowsWatcher.h>
#include <Activity/Activity.h>
#include <Core/StringEncoding.h>
#include <filesystem>
#include <iostream>

chronos::WindowsWatcher* chronos::WindowsWatcher::s_instance = nullptr;


chronos::WindowsWatcher::WindowsWatcher(const WindowsWatcherDesc& desc) : Base(desc.base)
{
	s_instance = this;
}

void chronos::WindowsWatcher::registerHooks()
{
    m_foregroundHook = SetWinEventHook(
        EVENT_SYSTEM_FOREGROUND,
        EVENT_SYSTEM_FOREGROUND,
        nullptr,
        WinEventProc,
        0,
        0,
        WINEVENT_OUTOFCONTEXT);
}

void chronos::WindowsWatcher::unregisterHooks()
{
    if (m_foregroundHook)
        UnhookWinEvent(m_foregroundHook);
    m_foregroundHook = nullptr;
}

chronos::WindowInfo chronos::WindowsWatcher::getCurrentForeground()
{
    return 	getWindowInfo(GetForegroundWindow());
}

chronos::WindowInfo chronos::WindowsWatcher::getWindowInfo(HWND hwnd)
{
    WindowInfo info{};
    if (!hwnd || !IsWindow(hwnd))
        return info;

    if (!IsWindowVisible(hwnd))
        return info;

    info.hwnd = hwnd;
    GetWindowThreadProcessId(info.hwnd, &info.pid);
    // Window Title
    {
        wchar_t buffer[512]{};
        GetWindowTextW(info.hwnd, buffer, _countof(buffer));
        info.title = chronos::WideToUtf8(buffer);
    }

    HANDLE process = OpenProcess(
        PROCESS_QUERY_LIMITED_INFORMATION,
        FALSE,
        info.pid);

    if (process)
    {
        wchar_t path[MAX_PATH];
        DWORD size = MAX_PATH;

        if (QueryFullProcessImageNameW(process, 0, path, &size))
        {
            std::filesystem::path p(path);
            info.processName = chronos::WideToUtf8(p.filename().wstring());
        }

        CloseHandle(process);
    }

    return info;
}

void chronos::WindowsWatcher::setWindowsChangedCallback(WindowChangedCallback callback)
{
    m_windowChangedCallback = callback;
}

void CALLBACK chronos::WindowsWatcher::WinEventProc(
    HWINEVENTHOOK hook,
    DWORD event,
    HWND hwnd,
    LONG idObject,
    LONG idChild,
    DWORD idEventThread,
    DWORD dwmsEventTime)
{
    if (!s_instance)
        return;

    switch (event)
    {
    case EVENT_SYSTEM_FOREGROUND:
        s_instance->handleForegroundChanged(hwnd);
        break;
    }
}

void chronos::WindowsWatcher::handleForegroundChanged(HWND hwnd)
{
    WindowInfo info = getWindowInfo(hwnd);
    //ChronosLogInfo(
    //    "pid: {}\n"
    //    "title: {}\n"
    //    "processName: {}\n\n",
    //    info.pid, info.title, info.processName);

    // Tell Monitor
    if (m_windowChangedCallback) {
        m_windowChangedCallback(info);
    }
}