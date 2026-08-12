#pragma once
#include <Core/Base.h>
#include <Plan/Plan.h>
#include <User/User.h>

namespace chronos
{
	class PlanManager : public Base
	{
	public:
		PlanManager(const PlanManagerDesc&);
		bool CreatePlan(Plan);
		bool UpdatePlan(Plan);
		bool removePlan(PlanId);
		void setCurrentUserId(UserId);
		std::vector<Plan> GetAllCurrentUserPlans();
	private:
		IPlanStorage& m_storage;
		UserId m_currentUserId = -1;
	};
}

