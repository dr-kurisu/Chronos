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
		explicit SQLiteActivityStorage(const SQLiteACStorageDesc& desc);
		~SQLiteActivityStorage() override;
		void configureDatabase();

		// User
		UserId createUser(const User& user) override;
		void updateUser(const User& user) override;
		void removeUser(UserId id) override;

		// Activity
		ActivityId insertActivity(const Activity& activity) override;
		void updateActivity(const Activity& activity) override;
		void removeActivity(ActivityId id) override;

		// Query
		std::optional<User> findUser(UserId id) override;
		std::optional<User> findUserByName(std::string name);
		std::vector<User> findAllUsers() override;
		std::optional<Activity> findActivity(ActivityId id) override;
		std::vector<Activity> findActivities(UserId userId);
		std::vector<Activity> findActivities(
			UserId userId,
			Timestamp begin,
			Timestamp end);

	protected:
		SQLiteActivityStorage(const SQLiteActivityStorage&) = delete;
		SQLiteActivityStorage& operator=(const SQLiteActivityStorage&) = delete;

	private:
		bool createTables();
		bool execute(std::string_view sql);
		bool execute(Statement& stmt);
		Statement prepare(std::string_view sql);
	private:
		sqlite3* m_db{};
	};
}


