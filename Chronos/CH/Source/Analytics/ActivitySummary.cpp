#include <Analytics/ActivitySummary.h>
#include <Analytics/ISummaryGenerator.h>

using namespace chronos;

ActivitySummary::ActivitySummary(const ActivitySummaryDesc& desc) : Base(desc.base), m_generator(desc.generator)
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
    auto& tagStatistics = summary.tagStatistics;
    tagStatistics.clear();
    for (const auto& ac : activities) 
    {
        auto duration = ac.duration().count();
        for (auto tag : AllActivityTags)
        {
            if (hasTag(ac.tags, tag))
            {
                tagStatistics[tag].count++;
                tagStatistics[tag].totalDuration += duration;
            }
        }
    }
}

void ActivitySummary::calculateApplicationStatistics(Summary& summary, const std::vector<Activity>& activities)
{

}
