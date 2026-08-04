#pragma once
#include <memory>
#include <string>
#include <cstdint>
#include <array>

#define disable_copy_and_move(Class)	\
protected:	\
	Class(const Class&) = delete;	\
	Class& operator=(const Class&) = delete;	\
	Class& operator=(Class&&) = delete;	\
	Class(Class&&) = delete; \

namespace chronos {
	using ActivityId = std::int64_t;
	using Timestamp = std::int64_t;
	using UserId = int;
	using TagId = int;
	using PlanId = std::int64_t;

	class Logger;
	class WindowsWatcher;
	class Monitor;
	class ActivityManager;
	class ActivityClassifier;
	class Statement;
	class IActivityStorage;
	class ISummaryGenerator;
	class IPlanStorage;
	class IUserStorage;
	class ITagStorage;
	class UserManager;
	class ActivitySummary;
	class PlanManager;
	class SQLiteDatabase;

	struct Activity;
	struct Plan;
	struct WindowInfo;
	struct Tag;

	template <typename T> using UniquePtr = std::unique_ptr<T>;
	template <typename T> using RefPtr = std::shared_ptr<T>;
}
