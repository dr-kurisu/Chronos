#pragma once
#include <string>
#include <Windows.h>
#include <chrono>
#include <Core/Core.h>
#include <User/User.h>
#include <Tag/Tag.h>

namespace chronos {
    struct WindowInfo
    {
        HWND hwnd{};
        DWORD pid{};
        std::string title{};
        std::string processName{};
    };

    enum class ActivityCategory
    {
        Unknown,
        Productive,
        Neutral,
        Distracting
    };

    struct Activity
    {
        ActivityId id{-1};
        UserId userId = -1;
        WindowInfo window;
        std::chrono::system_clock::time_point startTime;
        std::chrono::system_clock::time_point endTime;
        ActivityCategory category = ActivityCategory::Unknown;
        std::vector<TagId> tagIds;
        
        Activity() 
        {
        }

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

        bool isValid() const 
        {
            if (userId <= 0) return false;
            if (window.hwnd == nullptr) return false;
            if (window.pid == 0) return false;
            if (window.processName.empty()) return false;
            if (window.title.empty()) return false;
            if (endTime < startTime) return false;
            return true;
        }

        static int64_t convertTimePoint(std::chrono::system_clock::time_point timePoint)
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch()).count();
        }

        static std::chrono::system_clock::time_point convertTimestamp(int64_t timestamp)
        {
            return std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp));
        }
    };
}