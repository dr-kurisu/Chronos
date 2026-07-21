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
		void clear();
	private:
		std::vector<Activity> m_activities{};
	};
}