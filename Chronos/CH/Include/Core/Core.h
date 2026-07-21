#pragma once
//#include <stdexcept>
#include <memory>

#define disable_copy_and_move(Class)	\
protected:	\
	Class(const Class&) = delete;	\
	Class& operator=(const Class&) = delete;	\
	Class& operator=(Class&&) = delete;	\
	Class(Class&&) = delete; \

namespace chronos {
	class Logger;
	class WindowsWatcher;
	class Monitor;
	class ActivityManager;
	class ActivityClassifier;

	struct Activity;
	struct WindowInfo;



	template <typename T> using UniquePtr = std::unique_ptr<T>;
	template <typename T> using RefPtr = std::shared_ptr<T>;
}
