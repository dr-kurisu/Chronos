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

        template<typename T>
        static std::string vectorToString(
            const std::vector<T>& vec)
        {
            std::string result{ "[" };

            for (size_t i = 0; i < vec.size(); ++i)
            {
                if (i != 0)
                    result += ", ";

                result += std::format("{}", vec[i]);
            }

            result += "]";

            return result;
        }
    };
}