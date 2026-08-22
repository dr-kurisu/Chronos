#pragma once

#include <Core/Core.h>
#include <User/User.h>
#include <optional>

namespace chronos {
	class IUserStorage {
	public:
		virtual ~IUserStorage() = default;

		// User
		virtual UserId createUser(const User&) = 0;
		virtual bool updateUser(const User&) = 0;
		virtual bool removeUser(UserId) = 0;

		// Query
		virtual std::optional<User> findUser(UserId) = 0;
		virtual std::optional<User> findUserByUsername(std::string) = 0;
	};
}