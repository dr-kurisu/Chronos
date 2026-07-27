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
		void setCurrentUserId(UserId userId) noexcept;
		void clear();
	private:
		std::vector<Activity> m_activities{};
		UniquePtr<ActivityClassifier> m_classifier{};
		IActivityStorage& m_storage;
		UserId m_currentUserId{-1};
		std::chrono::seconds minDuration{ 10 };
	};
}