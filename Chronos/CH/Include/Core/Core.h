#pragma once
#include <memory>
#include <string>
#include <cstdint>

#define disable_copy_and_move(Class)	\
protected:	\
	Class(const Class&) = delete;	\
	Class& operator=(const Class&) = delete;	\
	Class& operator=(Class&&) = delete;	\
	Class(Class&&) = delete; \

namespace chronos {
	using UserId = std::int64_t;
	using ActivityId = std::int64_t;
	using Timestamp = std::int64_t;

	class Logger;
	class WindowsWatcher;
	class Monitor;
	class ActivityManager;
	class ActivityClassifier;
	class Statement;

	struct Activity;
	struct WindowInfo;


	struct User
	{
		UserId id{};
		std::string name;
		std::string passwordHash;
		Timestamp createdTime{};
	};

	template <typename T> using UniquePtr = std::unique_ptr<T>;
	template <typename T> using RefPtr = std::shared_ptr<T>;
}
