#pragma once
#include <Core/Base.h>
#include <Core/Core.h>
#include <Storage/SQLiteDatabase.h>
#include <Storage/IUserStorage.h>

namespace chronos {
	class SQLiteUserStorage : public Base, public IUserStorage {
	public:
		SQLiteUserStorage(const SQLiteStorageDesc& desc);
		~SQLiteUserStorage() override;

		// User
		UserId createUser(const User&) override;
		bool updateUser(const User&) override;
		bool removeUser(UserId) override;

		// Query
		std::optional<User> findUser(UserId) override;
		std::optional<User> findUserByUsername(std::string) override;

	private:
		bool createTable();
	private:
		SQLiteDatabase& m_db;
	};
}