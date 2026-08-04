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