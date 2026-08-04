#pragma once

#include <Core/Core.h>
#include <string>

namespace chronos 
{
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
		std::vector<TagId> tagIds;
		std::string createdAt;
		PlanStatus status;
	};
}
