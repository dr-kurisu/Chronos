#include <Plan/PlanManager.h>
#include <Storage/IPlanStorage.h>

using namespace chronos;

PlanManager::PlanManager(const PlanManagerDesc& desc):
	Base(desc.base), m_storage(desc.storage)
{
}

bool PlanManager::CreatePlan(Plan plan)
{
	plan.userId = m_currentUserId;
	if (!plan.isValid()) 
	{
		ChronosLogWarning("Fail to create invalid plan.");
		return false;
	}
	return m_storage.insertPlan(plan) > 0;
}

bool PlanManager::UpdatePlan(Plan plan)
{
	plan.userId = m_currentUserId;
	if (!plan.isValid())
	{
		ChronosLogWarning("Failed to update plan: invalid data.");
		return false;
	}
	return m_storage.updatePlan(plan);
}

bool PlanManager::removePlan(PlanId id)
{
	if (id <= 0)
	{
		ChronosLogWarning("Failed to delete plan: invalid id.");
		return false;
	}

	return m_storage.removePlan(m_currentUserId, id);
}

void PlanManager::setCurrentUserId(UserId id)
{
	if (id < 0) 
	{
		ChronosLogWarning("Fail to set current user plans with invalid userId.");
		return;
	}
	m_currentUserId = id;
}

std::vector<Plan> PlanManager::GetAllCurrentUserPlans()
{
	// Check userId
	if (m_currentUserId < 0) 
	{
		ChronosLogWarning("Fail to get current user plans with invalid userId.");
		return {};
	}
	return m_storage.findPlanByUser(m_currentUserId);
}

