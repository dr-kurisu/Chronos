#include <Core/Core.h>
#include <Core/Statement.h>
#include <User/User.h>
#include <Activity/Activity.h>
#include <Storage/SQLiteActivityStorage.h>
#include <Storage/SQliteDatabase.h>
#include <Tag/Tag.h>
#include <sqlite3.h>
#include <assert.h>
#include <unordered_map>

using namespace chronos;

SQLiteActivityStorage::SQLiteActivityStorage(const SQLiteStorageDesc& desc):
    Base(desc.base), m_db(desc.db)
{
    if (!createTable())
    {
        ChronosLogError("Failed to create ACSQLite tables.");
    }
}

SQLiteActivityStorage::~SQLiteActivityStorage()
{
}

ActivityId SQLiteActivityStorage::insertActivity(const Activity& activity)
{
    // check activity
    if (!activity.isValid()) 
    {
        ChronosLogWarning("Fail to insert invalid activity");
        return -1;
    }
    constexpr std::string_view sql = R"(
        INSERT INTO Activities
        (
            UserId,
            StartTime,
            EndTime,
            ProcessName,
            WindowTitle
        )
        VALUES
        (?, ?, ?, ?, ?);
    )";

    Statement stmt = m_db.prepare(sql);
    if (!stmt) return -1;
    // Bind params
    sqlite3_bind_int64(stmt.get(), 1, activity.userId);
    sqlite3_bind_int64(stmt.get(), 2, activity.convertTimePoint(activity.startTime));
    sqlite3_bind_int64(stmt.get(), 3, activity.convertTimePoint(activity.endTime));
    sqlite3_bind_text(stmt.get(), 4, activity.window.processName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.get(), 5, activity.window.title.c_str(), -1, SQLITE_TRANSIENT);

    if (!m_db.execute(stmt)) return -1;
    UserId id = static_cast<UserId>(sqlite3_last_insert_rowid(m_db.handle()));
    ChronosLogInfo("Create Activity successfully.   Activity id: {}", id);
    return id;
}

bool SQLiteActivityStorage::updateActivity(const Activity& activity)
{
    // Check activity
    if (!activity.isValid() || activity.id < 0) 
    {
        ChronosLogWarning("Failed to update invalid activity");
        return false;
    }
    constexpr std::string_view sql = R"(
        UPDATE Avtivities
        SET
            UserId = ?,
            StartTime = ?,
            EndTime = ?,
            ProcessName = ?,
            WindowTitle = ?,
        WHERE
            Id = ?;
    )";
    Statement stmt = m_db.prepare(sql);
    if (!stmt)
    {
        ChronosLogError(
            "Failed to update activity: {}",
            sqlite3_errmsg(m_db.handle()));
        return false;
    }
    sqlite3_bind_int64(stmt.get(), 1, activity.userId);
    sqlite3_bind_int64(stmt.get(), 2, activity.convertTimePoint(activity.startTime));
    sqlite3_bind_int64(stmt.get(), 3, activity.convertTimePoint(activity.endTime));
    sqlite3_bind_text(stmt.get(), 4, activity.window.processName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.get(), 5, activity.window.title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt.get(), 6, activity.id);

    if (!m_db.execute(stmt)) return false;
    if (sqlite3_changes(m_db.handle()) == 0) 
    {
        ChronosLogWarning("ActivityId: {} does not exist.", activity.id);
        return false;
    }
    ChronosLogInfo("Successfully update activity with Id: {}, title: {}", activity.id, activity.window.title);
    return true;
}

bool SQLiteActivityStorage::removeActivity(ActivityId id)
{
    // Check id
    if (id < 0) {
        ChronosLogWarning("Failed to remove activity with invalid id");
        return false;
    }
    // Prepare stmt
    constexpr std::string_view sql = R"(
        DELETE FROM Activities
        WHERE id = ?;
    )";
    Statement stmt = m_db.prepare(sql);
    if (!stmt) return false;
    // Bind params
    sqlite3_bind_int64(stmt.get(), 1, id);
    if (!m_db.execute(stmt)) return false;
    if (sqlite3_changes(m_db.handle()) == 0) 
    {
        ChronosLogWarning("ActivityId: {} does not exist.", id);
        return false;
    }
    return true;
}

bool SQLiteActivityStorage::addTags(ActivityId activityId, std::span<const TagId> tagIds)
{
    constexpr std::string_view sql = R"(
        INSERT INTO ActivityTags
        (
            ActivityId,
            TagId
        )
        VALUES
        (?, ?);
    )";
    Statement stmt = m_db.prepare(sql);
    if (!stmt) return false;
    for (const auto& tagId : tagIds)
    {
        sqlite3_bind_int64(stmt.get(), 1, activityId);
        sqlite3_bind_int64(stmt.get(), 2, tagId);
        if (!m_db.execute(stmt)) return false;
        sqlite3_reset(stmt.get());
    }
    return true;
}

bool SQLiteActivityStorage::removeTag(ActivityId activityId, TagId tagId)
{
    // Check params
    if (activityId < 0 || tagId < 0) 
    {
        ChronosLogWarning("Failed to removeTag with invalid params");
        return false;
    }
    constexpr std::string_view sql = R"(
        DELETE FROM ActivityTags
        WHERE ActivityId = ?
          AND TagId = ?;
    )";
    Statement stmt = m_db.prepare(sql);
    if (!stmt) return false;
    sqlite3_bind_int64(stmt.get(), 1, activityId);
    sqlite3_bind_int64(stmt.get(), 2, tagId);
    if (!m_db.execute(stmt)) return false;
    if (sqlite3_changes(m_db.handle()) == 0) 
    {
        ChronosLogWarning("Fail to remove TagId: {} with ActivityId: {}.", tagId, activityId);
        return false;
    }
    return true;
}

std::vector<Activity> SQLiteActivityStorage::findActivities(UserId userId, Timestamp begin, Timestamp end)
{   
    std::vector<Activity> activities;
    // Check params
    if (userId < 0)
    {
        ChronosLogWarning("Failed to findActivity with invalid userId");
        return activities;
    }
    if (end < begin) 
    {
        ChronosLogWarning("Failed to findActivity with invalid timestamp");
        return activities;
    }

    constexpr std::string_view sql = R"(
        SELECT
            a.Id,
            a.UserId,
            a.ProcessName,
            a.WindowTitle,
            a.StartTime,
            a.EndTime,
            t.TagId
        FROM Activities a
        LEFT JOIN ActivityTags t
        ON a.Id = t.ActivityId
        WHERE a.UserId = ?
          AND a.StartTime < ?
          AND a.EndTime > ?
        ORDER BY a.StartTime;
    )";
    Statement stmt = m_db.prepare(sql);
    if (!stmt) return activities;
    // bind
    sqlite3_bind_int64(stmt.get(), 1, userId);
    sqlite3_bind_int64(stmt.get(), 2, end);
    sqlite3_bind_int64(stmt.get(), 3, begin);
    // step
    std::unordered_map<ActivityId, size_t> activityMap;
    while (sqlite3_step(stmt.get()) == SQLITE_ROW)
    {
        ActivityId id = sqlite3_column_int64(stmt.get(), 0);
        size_t index;
        auto it = activityMap.find(id);
        // First added into map
        if (it == activityMap.end()) {
            Activity ac;
            ac.id = sqlite3_column_int64(stmt.get(), 0);
            ac.userId = sqlite3_column_int(stmt.get(), 1);
            ac.window.processName =
                reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 2));
            ac.window.title =
                reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 3));
            ac.startTime = Activity::convertTimestamp(sqlite3_column_int64(stmt.get(), 4));
            ac.endTime = Activity::convertTimestamp(sqlite3_column_int64(stmt.get(), 5));
            activities.push_back(std::move(ac));
            index = activities.size() - 1;
            activityMap.emplace(id, index);
        }
        // Already in the map
        else  {
            index = it->second;
        }
        // If has tag
        if (sqlite3_column_type(stmt.get(), 6) != SQLITE_NULL)
        {
            activities[index].tagIds.push_back(
                sqlite3_column_int(stmt.get(), 6
            ));
        }
    }
    return activities;
}

bool SQLiteActivityStorage::hasTag(ActivityId id, TagId tagId)
{
    constexpr std::string_view sql = R"(
        SELECT 1
        FROM ActivityTags
        WHERE ActivityId = ?
          AND TagId = ?
        LIMIT 1;
    )";;
    Statement stmt = m_db.prepare(sql);
    if (!stmt)
        return false;

    sqlite3_bind_int64(stmt.get(), 1, id);
    sqlite3_bind_int64(stmt.get(), 2, tagId);

    return sqlite3_step(stmt.get()) == SQLITE_ROW;
}

std::vector<TagId> chronos::SQLiteActivityStorage::getAllTags(ActivityId activityId)
{
    if (activityId < 0) 
    {
        ChronosLogWarning("Failed to getAllTags with invalid activityId");
        return {};
	}
    constexpr std::string_view sql = R"(
        SELECT TagId
        FROM ActivityTags
        WHERE ActivityId = ?;
    )";

	Statement stmt = m_db.prepare(sql);
    if (!stmt) return {};
    sqlite3_bind_int64(stmt.get(), 1, activityId);
    std::vector<TagId> tagIds;
    while (sqlite3_step(stmt.get()) == SQLITE_ROW)
    {
        tagIds.push_back(sqlite3_column_int(stmt.get(), 0));
    }
	return tagIds;
}

bool SQLiteActivityStorage::createTable()
{
    bool success = true;
    // Create Activity Table
    success &= m_db.execute(R"(
        CREATE TABLE IF NOT EXISTS Activities
        (
            Id           INTEGER PRIMARY KEY AUTOINCREMENT,
            UserId       INTEGER NOT NULL,
            StartTime    INTEGER NOT NULL,
            EndTime      INTEGER NOT NULL,
            ProcessName  TEXT NOT NULL,
            WindowTitle  TEXT NOT NULL,
            FOREIGN KEY(UserId) REFERENCES Users(Id) ON DELETE CASCADE
        );
    )");

    success &= m_db.execute(R"(
        CREATE INDEX IF NOT EXISTS idx_activity_user_start
        ON Activities(UserId, StartTime);
    )");

    // ActivityTags
    success &= m_db.execute(R"(
        CREATE TABLE IF NOT EXISTS ActivityTags
        (
            ActivityId INTEGER NOT NULL,
            TagId      INTEGER NOT NULL,

            PRIMARY KEY(ActivityId, TagId),

            FOREIGN KEY(ActivityId) REFERENCES Activities(Id)
                ON DELETE CASCADE,

            FOREIGN KEY(TagId) REFERENCES Tags(Id)
                ON DELETE CASCADE
        );
    )");

    success &= m_db.execute(R"(
        CREATE INDEX IF NOT EXISTS idx_activity_tags_tag
        ON ActivityTags(TagId);
    )");

    return success;
}