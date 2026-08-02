#pragma once

#include <Core/Base.h>
#include <Core/Core.h>
#include <filesystem>
#include <Activity/Activity.h>
#include <Activity/IActivityStorage.h>

#include <sqlite3.h>

namespace chronos {
	class SQLiteActivityStorage : public Base, public IActivityStorage {
	public:
		explicit SQLiteActivityStorage(const SQLiteStorageDesc& desc);
		~SQLiteActivityStorage() override;

		// User
		UserId createUser(const User& user) override;
		bool updateUser(const User& user) override;
		bool removeUser(UserId id) override;

		// Activity
		ActivityId insertActivity(const Activity& activity) override;
		bool updateActivity(const Activity& activity) override;
		bool removeActivity(ActivityId id) override;

		// Query
		std::optional<User> findUser(UserId id) override;
		std::optional<User> findUserByName(std::string name) override;
		std::vector<Activity> findActivities(UserId userId, Timestamp begin, Timestamp end) override;

	protected:
		SQLiteActivityStorage(const SQLiteActivityStorage&) = delete;
		SQLiteActivityStorage& operator=(const SQLiteActivityStorage&) = delete;

	private:
		bool createTables();
	private:
		SQLiteDatabase& m_db;
	};
}


