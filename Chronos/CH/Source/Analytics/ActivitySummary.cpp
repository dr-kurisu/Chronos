#include <Analytics/ActivitySummary.h>
#include <Analytics/ISummaryGenerator.h>
#include <Storage/IActivityStorage.h>
#include <Storage/ITagStorage.h>

using namespace chronos;

ActivitySummary::ActivitySummary(const ActivitySummaryDesc& desc) : 
    Base(desc.base), m_generator(desc.generator), m_tagStorage(desc.tagStorage), m_acStorage(desc.acStorage)
{
}

Summary ActivitySummary::generate(Timestamp begin, Timestamp end)
{
    auto activities = m_acStorage.findActivities(m_currentUserId, begin, end);
    // Generate Statistics Info
    Summary result{};
    calculateTagStatistics(result, activities);
    calculateApplicationStatistics(result, activities);

    // Generate Text with default generator
    result.text = m_generator.generate(result);
    return result;
}

std::chrono::seconds chronos::ActivitySummary::calculateTotalDuration(Timestamp begin, Timestamp end)
{
    const auto beginTime = Activity::convertTimestamp(begin);
    const auto endTime = Activity::convertTimestamp(end);
    auto result = m_acStorage.findActivities(m_currentUserId, begin, end);
    std::chrono::seconds totalDuration{0};
    for (auto& ac : result) 
    {
        if (ac.hasTag(BuiltinTagId::Idle)) continue;
        const auto activityBegin = std::max(ac.startTime, beginTime);
        const auto activityEnd = std::min(ac.endTime, endTime);
        if (activityBegin < activityEnd)
        {
            totalDuration += std::chrono::duration_cast<std::chrono::seconds>(activityEnd - activityBegin);
        }
    }
    return totalDuration;
}

void chronos::ActivitySummary::setCurrentUserId(UserId id)
{
    if (id < 0) return;
    m_currentUserId = id;
}


void ActivitySummary::calculateTagStatistics(Summary& summary, const std::vector<Activity>& activities)
{
    if (activities.empty()) return;
    auto& tagStatistics = summary.tagStatistics;
    tagStatistics.clear();

    auto allActivityTags = m_tagStorage.getAllTags(activities[0].userId);
    for (const auto& ac : activities) 
    {
        auto duration = ac.duration().count();
        
        for (auto& tag : allActivityTags)
        {
            if (m_acStorage.hasTag(ac.id, tag.id))
            {
                tagStatistics[tag.id].count++;
                tagStatistics[tag.id].totalDuration += duration;
            }
        }
    }
}

void ActivitySummary::calculateApplicationStatistics(Summary& summary, const std::vector<Activity>& activities)
{

}
