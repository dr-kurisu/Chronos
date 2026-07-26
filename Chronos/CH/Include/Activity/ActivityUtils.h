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
        static std::string tagToString(ActivityTags tags);
        static std::string tagsToString(ActivityTags tags);
    };
}