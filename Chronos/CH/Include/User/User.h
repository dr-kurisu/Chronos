#pragma once
#include <string>
#include <cstdint>
#include <Core/Core.h>

namespace chronos {
	struct User
	{
		std::string username;
		std::string passwordHash;

		UserId id{ -1 };
		std::string name{ "Default" };
		Timestamp createdTime{};

		bool isValid() const
		{
			return !name.empty() && !passwordHash.empty() && !username.empty();
		}
	};
}
