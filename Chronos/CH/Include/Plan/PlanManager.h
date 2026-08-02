#pragma once
#include <Core/Base.h>
#include <Plan/Plan.h>
#include <User/User.h>

namespace chronos
{
	class PlanManager : public Base
	{
	public:
		PlanManager(const PlanManagerDesc& desc);
		bool CreatePlan();
		bool UpdatePlan();
		bool DeletePlan();
		std::vector<Plan> GetCurrentUserPlans(UserId userId);
	private:
		IActivityStorage& m_storage;
	};
}

