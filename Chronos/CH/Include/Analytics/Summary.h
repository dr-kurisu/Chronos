#pragma once
#include <unordered_map>
#include <Core/Base.h>
#include <Activity/Activity.h>

namespace chronos 
{
    struct TagStatistics
    {
        size_t count{ 0 };
        uint64_t totalDuration{ 0 };
    };
    struct Summary
    {
        Timestamp begin;
        Timestamp end;

        std::string text;

        std::unordered_map<TagId, TagStatistics> tagStatistics;
        std::unordered_map<std::string, TagStatistics> applicationStatistics;
    };
}
