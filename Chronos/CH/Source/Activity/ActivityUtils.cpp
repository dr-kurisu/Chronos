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

    std::string ActivityUtils::tagToString(ActivityTags tags)
    {
        switch (tags)
        {
        case ActivityTags::Browser:     return "Browser";
        case ActivityTags::Code:        return "Code";
        case ActivityTags::Study:       return "Study";
        case ActivityTags::Work:        return "Work";
        case ActivityTags::Game:        return "Game";
        case ActivityTags::Video:       return "Video";
        case ActivityTags::Music:       return "Music";
        case ActivityTags::Chat:        return "Chat";
        case ActivityTags::Social:      return "Social";
        case ActivityTags::FileManager: return "FileManager";
        case ActivityTags::Terminal:    return "Terminal";
        case ActivityTags::Trash:       return "Trash";
        case ActivityTags::None:        return "None";
        }

        return "Unknown";
    }

    std::string ActivityUtils::tagsToString(ActivityTags tags)
    {
        if (tags == ActivityTags::None)
            return "None";

        std::string result;

        auto append = [&](ActivityTags tag)
            {
                if ((static_cast<uint32_t>(tags) &
                    static_cast<uint32_t>(tag)) != 0)
                {
                    if (!result.empty())
                        result += ", ";

                    result += tagToString(tag);
                }
            };

        append(ActivityTags::Browser);
        append(ActivityTags::Code);
        append(ActivityTags::Study);
        append(ActivityTags::Work);
        append(ActivityTags::Game);
        append(ActivityTags::Video);
        append(ActivityTags::Music);
        append(ActivityTags::Chat);
        append(ActivityTags::Social);
        append(ActivityTags::FileManager);
        append(ActivityTags::Terminal);
        append(ActivityTags::Trash);

        return result;
    }
}