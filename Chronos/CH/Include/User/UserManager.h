#pragma once

#include <Core/Base.h>
#include <Core/Core.h>
#include <User/User.h>
#include <optional>

namespace chronos 
{
	class UserManager : public Base
	{
	public:
		explicit UserManager(const UserManagerDesc& desc);
		bool registerUser(
			const std::string& username,
			const std::string& password
		);
		bool login(
			const std::string& username,
			const std::string& password
		);
		void logout();

		bool isLoggedIn() const;

		std::optional<User> getCurrentUser() const;

		UserId getCurrentUserId() const;

		bool verifyPassword(const std::string& password, const std::string& passwordHash);
		std::string hashPassword(const std::string& password) const;
	private:
		std::array<uint8_t, 16> generateSalt() const;
	private:
		IUserStorage& m_storage;
		std::optional<User> m_currentUser;
	};
}

