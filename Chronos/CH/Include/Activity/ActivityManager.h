#pragma once

#include <Core/Base.h>
#include <Activity/IActivityStorage.h>

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
		UniquePtr<ActivityClassifier> m_classifier{};
		UniquePtr<IActivityStorage> m_storage{};

		std::chrono::seconds minDuration{ 10 };
	};
}