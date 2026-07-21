#include <Activity/ActivityUtils.h>
#include <iomanip>
#include <sstream>
#include <Core/Logger.h>

namespace chronos
{

    std::string ActivityUtils::timePointToString(
        const std::chrono::system_clock::time_point& time)
    {
        auto t = std::chrono::system_clock::to_time_t(time);

        std::tm tm{};
        localtime_s(&tm, &t);

        std::stringstream ss;

        ss << std::put_time(
            &tm,
            "%Y-%m-%d %H:%M:%S"
        );

        return ss.str();
    }

    std::string ActivityUtils::tagToString(ActivityTag tag)
    {
        switch (tag)
        {
        case ActivityTag::Browser:      return "Browser";
        case ActivityTag::Code:         return "Code";
        case ActivityTag::Study:        return "Study";
        case ActivityTag::Work:         return "Work";
        case ActivityTag::Game:         return "Game";
        case ActivityTag::Video:        return "Video";
        case ActivityTag::Music:        return "Music";
        case ActivityTag::Chat:         return "Chat";
        case ActivityTag::Social:       return "Social";
        case ActivityTag::FileManager:  return "FileManager";
        case ActivityTag::Terminal:     return "Terminal";
        case ActivityTag::Trash:        return "Trash";
        }

        return "Unknown";
    }

    std::string ActivityUtils::tagsToString(const std::unordered_set<ActivityTag>& tags)
    {
        if (tags.empty())
            return "None";

        std::string result;

        for (const auto& tag : tags)
        {
            if (!result.empty())
                result += ", ";

            result += tagToString(tag);
        }

        return result;
    }
}