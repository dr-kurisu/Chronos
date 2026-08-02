#pragma once
#include <Core/Base.h>
#include <Storage/IPlanStorager.h>
#include <sqlite3.h>

namespace chronos
{
	class SQLitePlanStorage : public Base, public IPlanStorage {
	public:
		SQLitePlanStorage(const SQLiteStorageDesc& desc);
		~SQLitePlanStorage();
		PlanId insert(const Plan&) override;
		bool update(const Plan&) override;
		bool remove(PlanId) override;
		std::optional<Plan> find(PlanId) override;
		std::vector<Plan> findByUser(
			UserId,
			Timestamp,
			Timestamp) override;

	private:
		sqlite3* m_db{};
	};
}