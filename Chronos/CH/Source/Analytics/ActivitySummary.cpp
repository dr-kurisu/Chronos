#include <Analytics/ActivitySummary.h>
#include <Analytics/ISummaryGenerator.h>
#include <Storage/IActivityStorage.h>
#include <Storage/ITagStorage.h>

using namespace chronos;

ActivitySummary::ActivitySummary(const ActivitySummaryDesc& desc) : 
    Base(desc.base), m_generator(desc.generator), m_tagStorage(desc.tagStorage), m_acStorage(desc.acStorage)
{
}

Summary ActivitySummary::generate(const std::vector<Activity>& activities)
{
    // Generate Statistics Info
    Summary result{};
    calculateTagStatistics(result, activities);
    calculateApplicationStatistics(result, activities);

    // Generate Text with default generator
    result.text = m_generator.generate(result);
    return result;
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
        
        for (auto tag : allActivityTags)
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
