#pragma once
#include <string>
#include <Windows.h>
#include <chrono>
#include <unordered_set>

namespace chronos {
    struct WindowInfo
    {
        HWND hwnd;
        DWORD pid;
        std::string title;
        std::string processName;
    };

    enum class ActivityCategory
    {
        Unknown,
        Productive,
        Neutral,
        Distracting
    };

    enum class ActivityTag
    {
        Browser,
        Code,
        Study,
        Work,
        Game,
        Video,
        Music,
        Chat,
        Social,
        FileManager,
        Terminal,
        Trash
    };

    struct Activity
    {
        WindowInfo window;
        std::chrono::system_clock::time_point startTime;
        std::chrono::system_clock::time_point endTime;
        ActivityCategory category = ActivityCategory::Unknown;
        std::unordered_set<ActivityTag> tags;

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