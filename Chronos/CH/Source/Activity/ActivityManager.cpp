#include <Activity/ActivityManager.h>
#include <Activity/Activity.h>
#include <Activity/ActivityUtils.h>

chronos::ActivityManager::ActivityManager(const ActivityManagerDesc& desc): Base(desc.base)
{
}

chronos::ActivityManager::~ActivityManager()
{
}

void chronos::ActivityManager::createCurrentActivity(const WindowInfo& info)
{
	Activity activity{info};
	m_activities.push_back(activity);
}

void chronos::ActivityManager::endCurrentActivity()
{
    if (m_activities.empty())
    {
        return;
    }
	m_activities.back().finish();
}

const chronos::Activity* chronos::ActivityManager::getCurrentActivity() const
{
    return &m_activities.back();
}

void chronos::ActivityManager::printCurrentActivity()
{
    if (m_activities.empty()) return;
    Activity activity = m_activities.back();
    ChronosLogInfo(
        "Activity:\n"
        "PID: {}\n"
        "Title: {}\n"
        "Process: {}\n"
        "Start: {}\n"
        "End: {}\n\n",
        activity.window.pid,
        activity.window.title,
        activity.window.processName,
        ActivityUtils::timePointToString(activity.startTime),
        ActivityUtils::timePointToString(activity.endTime)
    );  
}

void chronos::ActivityManager::clear()
{
    m_activities.clear();
}