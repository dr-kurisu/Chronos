#pragma once

#include <Core/Base.h>

namespace chronos {
	class ActivityManager : public Base {
	public:
		ActivityManager(const ActivityManagerDesc& desc);
		~ActivityManager();

		void createCurrentActivity(const WindowInfo& info);
		void endCurrentActivity();
		const Activity* getCurrentActivity() const;
		void printCurrentActivity();
		void classifyCurrentActivity();
		void onWindowChanged(const WindowInfo& info);
		void clear();
	private:
		std::vector<Activity> m_activities{};
		std::chrono::seconds minDuration{ 10 };
		UniquePtr<ActivityClassifier> m_classifier{};
	};
}