#pragma once

#include <Core/Core.h>
#include <Core/Base.h>
#include <User/User.h>
#include <optional>

namespace chronos 
{
	class UserManager : public Base
	{
	public:
		explicit UserManager(const UserManagerDesc& desc);
		std::optional<UserId> registerUser(
			const std::string& username,
			const std::string& password,
			const std::string& name
		);

		std::optional<UserId> login(
			const std::string& username,
			const std::string& password
		);

		bool verifyPassword(const std::string& password, const std::string& passwordHash);

		std::string hashPassword(const std::string& password) const;

		std::optional<User> findUser(const UserId userId) const;

	private:
		std::array<uint8_t, 16> generateSalt() const;

	private:
		IUserStorage& m_storage;
	};
}