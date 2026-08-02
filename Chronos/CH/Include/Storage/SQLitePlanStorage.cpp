#include <Storage/SQLitePlanStorage.h>

using namespace chronos;

SQLitePlanStorage::SQLitePlanStorage(const SQLiteStorageDesc& desc):
	Base(desc.base)
{

}

SQLitePlanStorage::~SQLitePlanStorage()
{
}

PlanId chronos::SQLitePlanStorage::insert(const Plan&)
{
	return PlanId();
}

bool chronos::SQLitePlanStorage::update(const Plan&)
{
	return false;
}

bool chronos::SQLitePlanStorage::remove(PlanId)
{
	return false;
}

std::optional<Plan> chronos::SQLitePlanStorage::find(PlanId)
{
	return std::optional<Plan>();
}

std::vector<Plan> chronos::SQLitePlanStorage::findByUser(UserId, Timestamp, Timestamp)
{
	return std::vector<Plan>();
}
