#pragma once
#include <Storage/IPlanStorage.h>
#include <Core/Base.h>
#include <sqlite3.h>


namespace chronos
{
	class SQLitePlanStorage : public Base, public IPlanStorage {
	public:
		explicit SQLitePlanStorage(const SQLiteStorageDesc& desc);
		~SQLitePlanStorage() override;
		PlanId insertPlan(const Plan&) override;
		bool updatePlan(const Plan&) override;
		bool removePlan(UserId, PlanId) override;
		std::optional<Plan> findPlan(PlanId) override;
		std::vector<Plan> findPlanByUser(
			UserId,
			Timestamp,
			Timestamp) override;
		std::vector<Plan> findPlanByUser(UserId) override;
	private:
		bool createTable();
		std::optional<Plan> readPlan(sqlite3_stmt* stmt);
	private:
		SQLiteDatabase& m_db;
	};
}