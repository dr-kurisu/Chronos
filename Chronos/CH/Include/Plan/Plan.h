#pragma once
#include <string>
#include <Activity/ActivityTag.h>


namespace chronos 
{
	using PlanId = std::int64_t;
	enum class PlanStatus
	{
		Todo,
		InProgress,
		Done
	};

	enum class PlanPriority
	{
		P0,
		P1,
		P2,
		P3
	};

	struct Plan
	{
		PlanId id;
		std::string title;
		std::string description{};
		std::string startTime{};
		std::string endTime{};
		PlanPriority priority;
		ActivityTags tags;
		std::string createdAt;
		PlanStatus status;
	};
}
