#include <Activity/ActivityManager.h>
#include <Activity/Activity.h>
#include <Activity/ActivityUtils.h>
#include <Activity/ActivityClassifier.h>
#include <Storage/SQLiteActivityStorage.h>
#include <User/AuthContext.h>

chronos::ActivityManager::ActivityManager(const ActivityManagerDesc& desc): 
	Base(desc.base), 
    minDuration(desc.minDuration), 
    m_storage(desc.storage),
    m_authContext(desc.authContext)
{
    m_classifier = std::make_unique<ActivityClassifier>(ActivityClassifierDesc{ desc.base });
}

chronos::ActivityManager::~ActivityManager()
{
}

void chronos::ActivityManager::createCurrentActivity(const WindowInfo& info)
{
	Activity ac{info};
    const auto userId = m_authContext.userId();

    if (!userId) return;
    ac.userId = *userId;
	m_activities.push_back(ac);
    if (m_activities.size() > 100) m_activities.pop_front();
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
        "TagIds: {}\n"
        "Start: {}\n"
        "End: {}\n\n",
        ac->userId,
        ac->window.pid,
        ac->window.title,
        ac->window.processName,
        ActivityUtils::tagIdsToString(ac->tagIds, m_tagMap),
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
        createCurrentActivity(info);
        return;
    }

    // Classification
    classifyCurrentActivity();
    // Storage
    const Activity& activity = m_activities.back();
    ActivityId id = m_storage.insertActivity(activity);
    m_storage.addTags(id, activity.tagIds);
    printCurrentActivity();
    createCurrentActivity(info);
}

void chronos::ActivityManager::updateTagMap(std::unordered_map<TagId, Tag> map)
{
    // Pass by value
    m_tagMap = map;
}


void chronos::ActivityManager::clear()
{
    m_activities.clear();
}