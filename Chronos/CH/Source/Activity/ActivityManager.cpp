#include <Activity/ActivityManager.h>
#include <Activity/Activity.h>
#include <Activity/ActivityUtils.h>
#include <Activity/ActivityClassifier.h>
#include <Storage/SQLiteActivityStorage.h>

chronos::ActivityManager::ActivityManager(const ActivityManagerDesc& desc): Base(desc.base), minDuration(desc.minDuration), m_storage(desc.storage)
{
    m_classifier = std::make_unique<ActivityClassifier>(ActivityClassifierDesc{ desc.base });
}

chronos::ActivityManager::~ActivityManager()
{
}

void chronos::ActivityManager::createCurrentActivity(const WindowInfo& info)
{
	Activity ac{info};
    ac.userId = m_currentUserId;
	m_activities.push_back(ac);
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
    if (m_activities.empty())
        return nullptr;
    return &m_activities.back();
}

void chronos::ActivityManager::printCurrentActivity()
{
    if (m_activities.empty()) return;
    const Activity* ac = getCurrentActivity();
    if (!ac) return;
    ChronosLogInfo(
        "Activity:\n"
        "UserId: {}\n"
        "PID: {}\n"
        "Title: {}\n"
        "Process: {}\n"
        "Tags: {}\n"
        "Start: {}\n"
        "End: {}\n\n",
        ac->userId,
        ac->window.pid,
        ac->window.title,
        ac->window.processName,
        ActivityUtils::tagsToString(ac->tags),
        ActivityUtils::timePointToString(ac->startTime),
        ActivityUtils::timePointToString(ac->endTime)
    );
}

void chronos::ActivityManager::classifyCurrentActivity()
{
    m_classifier->classify(m_activities.back());
}

void chronos::ActivityManager::onWindowChanged(const WindowInfo& info)
{
    endCurrentActivity();
    const Activity* ac = getCurrentActivity();
    // no activity exisit
    if (!ac) {
        createCurrentActivity(info);
        return;
    }
    // permission check
    if (ac->window.pid == 0) {
        ChronosLogInfo("No permission to access current activity.");
        createCurrentActivity(info);
        return;
    }

    // duration check
    if (ac->duration() < minDuration) {
        // ChronosLogInfo("Duration is less than {}.", minDuration);
        createCurrentActivity(info);
        return;
    }

    // Classification
    classifyCurrentActivity();

    printCurrentActivity();
    createCurrentActivity(info);
}

void chronos::ActivityManager::setCurrentUserId(UserId userId) noexcept
{
    if (userId < 0) 
    {
        ChronosLogWarning("Failed to set current userId.");
        return;
    }
    m_currentUserId = userId;
}


void chronos::ActivityManager::clear()
{
    m_activities.clear();
}