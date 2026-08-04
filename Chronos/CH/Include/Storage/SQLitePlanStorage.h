#pragma once
#include <Core/Base.h>
#include <Storage/IPlanStorager.h>
#include <sqlite3.h>

namespace chronos
{
	class SQLitePlanStorage : public Base, public IPlanStorage {
	public:
		explicit SQLitePlanStorage(const SQLiteStorageDesc& desc);
		~SQLitePlanStorage();
		PlanId insertPlan(const Plan&) override;
		bool updatePlan(const Plan&) override;
		bool removePlan(PlanId) override;
		std::optional<Plan> findPlan(PlanId) override;
		std::vector<Plan> findPlanByUser(
			UserId,
			Timestamp,
			Timestamp) override;
	private:
		bool createTable();

	private:
		SQLiteDatabase& m_db;
	};
}