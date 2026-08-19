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
	class ActivityClassifier;
	class Statement;
	class IActivityStorage;
	class ISummaryGenerator;
	class IPlanStorage;
	class IUserStorage;
	class ITagStorage;
	class ActivitySummary;
	class SQLiteDatabase;

	class UserManager;
	class ActivityManager;
	class TagManager;
	class PlanManager;
	class WebViewController;
	class Window;
	class Rect;
	class Backend;
	class ActivityController;
	class UserController;


	struct Activity;
	struct Plan;
	struct WindowInfo;
	struct Tag;


	using i32 = int;
	using ui32 = unsigned int;
	using f32 = float;
	using d64 = double;

	template <typename T> using UniquePtr = std::unique_ptr<T>;
	template <typename T> using RefPtr = std::shared_ptr<T>;
}
