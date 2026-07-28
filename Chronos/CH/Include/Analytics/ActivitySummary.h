#pragma once

#include <Analytics/Summary.h>
#include <Analytics/ISummaryGenerator.h>

namespace chronos 
{
	class ActivitySummary : public Base
	{
	public:
		ActivitySummary(const ActivitySummaryDesc& desc);
        Summary generate(const std::vector<Activity>& activities);

    private:
        void calculateTagStatistics(Summary& summary, const std::vector<Activity>& activities);
        void calculateApplicationStatistics(Summary& summary, const std::vector<Activity>& activities);

	private:
		ISummaryGenerator& m_generator;
	};
}

