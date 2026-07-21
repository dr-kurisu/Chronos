#pragma once

#include <string>
#include <Activity/Activity.h>

namespace chronos
{
    class ActivityUtils
    {
    public:
        static std::string timePointToString(
            const std::chrono::system_clock::time_point& time
        );
        static std::string tagToString(ActivityTag tag);
        static std::string tagsToString(const std::unordered_set<ActivityTag>& tags);
    };
}