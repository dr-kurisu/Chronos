#pragma once

#include <Core/Base.h>
#include <Storage/IActivityStorage.h>
#include <unordered_map>
#include <deque>

namespace chronos {
	class ActivityManager : public Base {
	public:
		explicit ActivityManager(const ActivityManagerDesc& desc);
		~ActivityManager();

		void createCurrentActivity(const WindowInfo& info);
		void endCurrentActivity();

		const Activity* getCurrentActivity() const;
		void printCurrentActivity();

		void classifyCurrentActivity();
		void onWindowChanged(const WindowInfo& info);
		void setCurrentUserId(UserId userId) noexcept;
		void updateTagMap(std::unordered_map<TagId, Tag> map);
		void clear();
	private:
		std::deque<Activity> m_activities{};
		UniquePtr<ActivityClassifier> m_classifier{};
		IActivityStorage& m_storage;
		UserId m_currentUserId{-1};
		std::chrono::seconds minDuration{ 10 };
		std::unordered_map<TagId, Tag> m_tagMap;
	};
}