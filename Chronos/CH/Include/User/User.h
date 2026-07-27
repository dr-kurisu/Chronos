#pragma once
#include <string>
#include <cstdint>

namespace chronos {
	using UserId = std::int64_t;
	using Timestamp = std::int64_t;
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
