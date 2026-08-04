#pragma once
#include <string>
#include <cstdint>
#include <Core/Core.h>

namespace chronos {
	struct User
	{
		UserId id{ -1 };
		std::string name;
		std::string passwordHash;
		Timestamp createdTime{};

		bool isValid() const
		{
			return !name.empty() && !passwordHash.empty();
		}
	};
}
