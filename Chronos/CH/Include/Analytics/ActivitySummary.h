#pragma once

#include <Core/Core.h>
#include <Analytics/Summary.h>
#include <Analytics/ISummaryGenerator.h>

namespace chronos 
{
	class ActivitySummary : public Base
	{
	public:
		ActivitySummary(const ActivitySummaryDesc& desc);
        Summary generate(Timestamp begin, Timestamp end);
		std::chrono::seconds calculateTotalDuration(Timestamp begin, Timestamp end);
		void setCurrentUserId(UserId);

    private:
        void calculateTagStatistics(Summary&, const std::vector<Activity>&);
        void calculateApplicationStatistics(Summary&, const std::vector<Activity>&);

	private:
		ISummaryGenerator& m_generator;
		IActivityStorage& m_acStorage;
		ITagStorage& m_tagStorage;
		UserId m_currentUserId = -1;
	};
}

