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
}