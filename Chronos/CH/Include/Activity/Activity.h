#pragma once
#include <string>
#include <Windows.h>

namespace chronos {
    struct WindowInfo
    {
        HWND hwnd;
        DWORD pid;
        std::string title;
        std::string processName;

        bool isValid() const
        {
            return hwnd != nullptr;
        }
    };

    struct Activity
    {
        std::string appName;
        std::string windowTitle;
        uint32_t pid;
    };
}