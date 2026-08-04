#include <Storage/SQLitePlanStorage.h>
#include <Storage/SQLiteDatabase.h>

using namespace chronos;

SQLitePlanStorage::SQLitePlanStorage(const SQLiteStorageDesc& desc) :
	Base(desc.base), m_db(desc.db)
{
	if (!createTable())
	{
		ChronosLogError("Failed to create PlanSQLite tables.");
	}
	ChronosLogInfo("PlanDatabase initialised");
}

SQLitePlanStorage::~SQLitePlanStorage()
{
}

PlanId SQLitePlanStorage::insertPlan(const Plan& plan)
{
	return -1;
}

bool SQLitePlanStorage::updatePlan(const Plan& plan)
{
	return false;
}

bool SQLitePlanStorage::removePlan(PlanId id)
{
	return false;
}

std::optional<Plan> SQLitePlanStorage::findPlan(PlanId id)
{
	return std::optional<Plan>();
}

std::vector<Plan> SQLitePlanStorage::findPlanByUser(UserId id, Timestamp start, Timestamp end)
{
	return std::vector<Plan>();
}

bool SQLitePlanStorage::createTable() 
{
	// Need modify
	bool success = true;
	success &= m_db.execute(R"(
		CREATE TABLE IF NOT EXISTS Plans
		(
			Id           INTEGER PRIMARY KEY AUTOINCREMENT,
			Title		 TEXT NOT NULL,
			Description  TEXT,
			StartTime	 INTEGER NOT NULL,
			EndTime		 INTEGER NOT NULL,
			Priority     INTEGER NOT NULL,
			Tags		 INTEGER NOT NULL
		);
	)");
	return success;
}
