#include <Plan/PlanManager.h>

using namespace chronos;

PlanManager::PlanManager(const PlanManagerDesc& desc):
	Base(desc.base), m_storage(desc.storage)
{
}


