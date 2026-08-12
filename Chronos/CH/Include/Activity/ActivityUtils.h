#pragma once

#include <Activity/Activity.h>
#include <string>
#include <unordered_map>


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

        static std::string tagIdsToString(
            const std::vector<TagId>& tagIds,
            const std::unordered_map<TagId, Tag>& tagMap)
        {
            std::string result{ "[" };

            for (size_t i = 0; i < tagIds.size(); ++i)
            {
                if (i != 0)
                    result += ", ";

                auto it = tagMap.find(tagIds[i]);

                if (it != tagMap.end())
                {
                    result += it->second.name;
                }
                else
                {
                    result += "Unknown";
                }
            }
            result += "]";
            return result;
        }
    };
}