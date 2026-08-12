#pragma once

#include <Core/Core.h>
#include <string>
#include <chrono>

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
		UserId userId;
		std::string title;
		std::string description{};
		std::chrono::system_clock::time_point startTime{};
		std::chrono::system_clock::time_point endTime{};
		PlanPriority priority;
		std::vector<TagId> tagIds;
		std::string createdAt;
		PlanStatus status;

		bool isValid() const
		{
			if (userId <= 0) return false;
			if (title.empty()) return false;
			if (endTime <= startTime) return false;
			// Tag validation
			for (auto tagId : tagIds)
			{
				if (tagId <= 0) return false;
			}
			return true;
		}

		static int64_t convertTimePoint(std::chrono::system_clock::time_point timePoint)
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch()).count();
		}

		static std::chrono::system_clock::time_point convertTimestamp(int64_t timestamp)
		{
			return std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp));
		}
	};
}
