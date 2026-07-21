#pragma once
#include <string>
#include <Windows.h>
#include <chrono>

namespace chronos {
    struct WindowInfo
    {
        HWND hwnd;
        DWORD pid;
        std::string title;
        std::string processName;
    };

    struct Activity
    {
        WindowInfo window;
        std::chrono::system_clock::time_point startTime;
        std::chrono::system_clock::time_point endTime;

        Activity(const WindowInfo& info)
            : window(info),
            startTime(std::chrono::system_clock::now()),
            endTime(startTime)
        {
        }

        void finish()
        {
            endTime = std::chrono::system_clock::now();
        }


        std::chrono::seconds duration() const
        {
            return std::chrono::duration_cast<std::chrono::seconds>(
                endTime - startTime
            );
        }
    };
}