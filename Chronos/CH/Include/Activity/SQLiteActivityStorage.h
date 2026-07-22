#pragma once

#include <Core/Core.h>
#include <filesystem>
#include <Activity/Activity.h>
#include <Core/Base.h>

namespace chronos {
	class SQLiteActivityStorage : public Base {
	public:
		explicit SQLiteActivityStorage(const SQLiteACStorageDesc& desc);
		~SQLiteActivityStorage();
		void configureDatabase();

		ActivityId insert(Activity& activity);
		void update(const Activity& activity);
		void remove(ActivityId id);

		std::optional<Activity> find(ActivityId id);
		std::vector<Activity> findAll();

	protected:
		SQLiteActivityStorage(const SQLiteActivityStorage&) = delete;
		SQLiteActivityStorage& operator=(const SQLiteActivityStorage&) = delete;

	private:
		bool createTables();
		bool execute(std::string_view sql);
		Statement prepare(std::string_view sql);
	private:
		sqlite3* m_db{};
	};
}


