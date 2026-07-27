#include <Activity/SQLiteActivityStorage.h>
#include <Activity/Statement.h>
#include <Activity/Activity.h>
#include <Activity/ActivityTag.h>
#include <User/User.h>
#include <sqlite3.h>
#include <assert.h>

using namespace chronos;

SQLiteActivityStorage::SQLiteActivityStorage(const SQLiteACStorageDesc& desc) : Base(desc.base)
{
    const int result = sqlite3_open(desc.storagePath.string().c_str(), &m_db);
    // Fail to open
    if (result != SQLITE_OK)
    {
        const std::string error =
            m_db ? sqlite3_errmsg(m_db) : "Unknown error";

        if (m_db)
        {
            sqlite3_close(m_db);
            m_db = nullptr;
        }

        throw std::runtime_error(
            "Failed to open SQLite database: " + error);
    }

    configureDatabase();
    if (!createTables())
    {
        ChronosLogError("Failed to create SQLite tables.");
    }
    ChronosLogInfo("Database initialised");
}

SQLiteActivityStorage::~SQLiteActivityStorage()
{
    if (m_db)
    {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
}

void SQLiteActivityStorage::configureDatabase()
{
    execute("PRAGMA foreign_keys = ON;");
}

UserId SQLiteActivityStorage::createUser(const User& user)
{
    std::optional<User> existUser = findUserByName(user.name);
    if (existUser)
    {
        ChronosLogWarning("Username: {} already exist", existUser->name);
        return -1;
    }
    if (!user.isValid()) 
    {
        ChronosLogWarning("Failed to createUser with Invalid user.");
        return -1;
    }

    constexpr std::string_view sql = R"(
        INSERT INTO Users
        (
            Name,
            PasswordHash,
            CreatedTime
        )
        VALUES
        (?, ?, ?);
    )";
    Statement stmt = prepare(sql);
    if (!stmt) return -1;

    sqlite3_bind_text(stmt.get(), 1, user.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.get(), 2, user.passwordHash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt.get(), 3, user.createdTime);

    if (!execute(stmt))
        return -1;

    UserId id = static_cast<UserId>(
        sqlite3_last_insert_rowid(m_db));

    ChronosLogInfo(
        "Created user successfully.   Id: {}, Name: {}",
        id,
        user.name);
    return id;
}

bool SQLiteActivityStorage::updateUser(const User& user)
{
    if (!user.isValid() || user.id < 0) 
    {
        ChronosLogWarning("Failed to update invalid user.");
        return false;
    }
    constexpr std::string_view sql = R"(
        UPDATE Users 
        SET
            Name = ?,
            PasswordHash = ?
        WHERE
            Id = ?;
    )";

    Statement stmt = prepare(sql);
    if (!stmt)
    {
        ChronosLogError(
            "Failed to update user: {}",
            sqlite3_errmsg(m_db));
        return false;
    }

    sqlite3_bind_text(stmt.get(), 1, user.name.c_str(), - 1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.get(), 2, user.passwordHash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt.get(), 3, user.id);

    if (!execute(stmt)) return false;
    
    if (sqlite3_changes(m_db) == 0)
    {
        ChronosLogWarning("UserId: {} does not exist.", user.id);
        return false;
    }
    ChronosLogInfo("Successfully update user with Id: {}, Name: {}", user.id, user.name);
    return true;
}

bool SQLiteActivityStorage::removeUser(UserId id)
{
    if (id < 0) {
        ChronosLogWarning("Failed to remove invalid userid.");
        return false;
    }
    constexpr std::string_view sql = R"(
        DELETE FROM Users
        WHERE Id = ?;
    )";

    Statement stmt = prepare(sql);
    if (!stmt) 
    {
        ChronosLogError(
            "Failed to remove user: {}",
            sqlite3_errmsg(m_db));
        return false;
    }

    sqlite3_bind_int64(stmt.get(), 1, id);
    if (!execute(stmt))
        return false;

    if (sqlite3_changes(m_db) == 0)
    {
        ChronosLogWarning("UserId: {} does not exist.", id);
        return false;
    }
    return true;
}

std::optional<User> SQLiteActivityStorage::findUser(UserId id)
{
    // check id
    if (id < 0) {
        ChronosLogWarning("Failed to findUser with invalid id");
        return std::nullopt;
    }
    constexpr std::string_view sql = R"(
        SELECT
            Id,
            Name, 
            PasswordHash,
            CreatedTime
        FROM Users
        WHERE Id = ?;
    )";
    Statement stmt = prepare(sql);
    if (!stmt) return std::nullopt;
    sqlite3_bind_int64(stmt.get(), 1, id);

    const int result = sqlite3_step(stmt.get());
    if (result == SQLITE_ROW)
    {
        User user;
        user.id = static_cast<UserId>(
            sqlite3_column_int64(stmt.get(), 0));
        user.name = reinterpret_cast<const char*>(
            sqlite3_column_text(stmt.get(), 1));
        user.passwordHash = reinterpret_cast<const char*>(
            sqlite3_column_text(stmt.get(), 2));
        user.createdTime = static_cast<Timestamp>(
            sqlite3_column_int64(stmt.get(), 3));
        return user;
    }

    if (result != SQLITE_DONE)
    {
        ChronosLogError(
            "Failed to find user: {}",
            sqlite3_errmsg(m_db));
    }

    return std::nullopt;
}

std::optional<User> SQLiteActivityStorage::findUserByName(std::string name)
{
    constexpr std::string_view sql = R"(
        SELECT
            Id,
            Name,
            PasswordHash,
            CreatedTime
        FROM Users
        WHERE Name = ?;
    )";

    Statement stmt = prepare(sql);
    if (!stmt)
        return std::nullopt;

    sqlite3_bind_text(stmt.get(), 1, name.c_str(), -1, SQLITE_TRANSIENT);

    const int result = sqlite3_step(stmt.get());
    if (result == SQLITE_ROW)
    {
        User user;
        user.id = static_cast<UserId>(
            sqlite3_column_int64(stmt.get(), 0));
        user.name = reinterpret_cast<const char*>(
            sqlite3_column_text(stmt.get(), 1));
        user.passwordHash = reinterpret_cast<const char*>(
            sqlite3_column_text(stmt.get(), 2));
        user.createdTime = static_cast<Timestamp>(
            sqlite3_column_int64(stmt.get(), 3));
        return user;
    }

    if (result != SQLITE_DONE)
    {
        ChronosLogError(
            "Failed to find user by name: {}",
            sqlite3_errmsg(m_db));
    }

    return std::nullopt;
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
            WindowTitle,
            Tag
        )
        VALUES
        (?, ?, ?, ?, ?, ?);
    )";

    Statement stmt = prepare(sql);
    if (!stmt) return -1;
    // Bind params
    sqlite3_bind_int64(stmt.get(), 1, activity.userId);
    sqlite3_bind_int64(stmt.get(), 2, activity.convertTimePoint(activity.startTime));
    sqlite3_bind_int64(stmt.get(), 3, activity.convertTimePoint(activity.endTime));
    sqlite3_bind_text(stmt.get(), 4, activity.window.processName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.get(), 5, activity.window.title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt.get(), 6, static_cast<int64_t>(activity.tags));

    if (!execute(stmt)) return -1;
    UserId id = static_cast<UserId>(
        sqlite3_last_insert_rowid(m_db));
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
            Tag = ?
        WHERE
            Id = ?;
    )";
    Statement stmt = prepare(sql);
    if (!stmt)
    {
        ChronosLogError(
            "Failed to update activity: {}",
            sqlite3_errmsg(m_db));
        return false;
    }
    sqlite3_bind_int64(stmt.get(), 1, activity.userId);
    sqlite3_bind_int64(stmt.get(), 2, activity.convertTimePoint(activity.startTime));
    sqlite3_bind_int64(stmt.get(), 3, activity.convertTimePoint(activity.endTime));
    sqlite3_bind_text(stmt.get(), 4, activity.window.processName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.get(), 5, activity.window.title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt.get(), 6, static_cast<int64_t>(activity.tags));
    sqlite3_bind_int64(stmt.get(), 7, activity.id);

    if (!execute(stmt)) return false;
    if (sqlite3_changes(m_db) == 0) 
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
    Statement stmt = prepare(sql);
    if (!stmt) return false;
    // Bind params
    sqlite3_bind_int64(stmt.get(), 1, id);
    if (!execute(stmt)) return false;
    if (sqlite3_changes(m_db) == 0) 
    {
        ChronosLogWarning("ActivityId: {} does not exist.", id);
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
        SELECT * FROM Activities
        WHERE UserId = ?
              AND StartTime < ?
              AND EndTime > ?
        ORDER BY StartTime ASC;
    )";
    Statement stmt = prepare(sql);
    if (!stmt) return activities;
    // bind
    sqlite3_bind_int64(stmt.get(), 1, userId);
    sqlite3_bind_int64(stmt.get(), 2, end);
    sqlite3_bind_int64(stmt.get(), 3, begin);
    // step
    const int result = sqlite3_step(stmt.get());
    while (sqlite3_step(stmt.get()) == SQLITE_ROW)
    {
        Activity activity;

        activity.id = sqlite3_column_int64(stmt.get(), 0);
        activity.userId = sqlite3_column_int64(stmt.get(), 1);

        activity.window.processName =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt.get(), 2)
                );

        activity.window.title =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt.get(), 3)
                );

        activity.startTime = Activity::convertTimestamp(sqlite3_column_int64(stmt.get(), 4));
           
        activity.endTime = Activity::convertTimestamp(sqlite3_column_int64(stmt.get(), 5));

        activity.tags = static_cast<ActivityTags>(sqlite3_column_int(stmt.get(), 6));

        activities.push_back(std::move(activity));
    }
    return activities;
}

bool SQLiteActivityStorage::createTables()
{
    bool success = true;
    // Create Sser Table
    success &= execute(R"(
        CREATE TABLE IF NOT EXISTS Users
        (
            Id           INTEGER PRIMARY KEY AUTOINCREMENT,
            Name         TEXT NOT NULL UNIQUE,
            PasswordHash TEXT NOT NULL,
            CreatedTime  INTEGER NOT NULL
        );
    )");
    // Create Activity Table
    success &= execute(R"(
        CREATE TABLE IF NOT EXISTS Activities
        (
            Id           INTEGER PRIMARY KEY AUTOINCREMENT,
            UserId       INTEGER NOT NULL,
            StartTime    INTEGER NOT NULL,
            EndTime      INTEGER NOT NULL,
            ProcessName  TEXT NOT NULL,
            WindowTitle  TEXT NOT NULL,
            Tag          INTEGER,

            FOREIGN KEY(UserId) REFERENCES Users(Id)
        );
    )");

    success &= execute(R"(
        CREATE INDEX IF NOT EXISTS idx_activity_user_start
        ON Activities(UserId, StartTime);
    )");

    return success;
}

bool SQLiteActivityStorage::execute(std::string_view sql)
{
    assert(m_db != nullptr);

    char* errorMessage = nullptr;

    const int result = sqlite3_exec(
        m_db,
        sql.data(),
        nullptr,
        nullptr,
        &errorMessage);

    if (result != SQLITE_OK)
    {
        ChronosLogError(
            "SQLite execute failed.\nSQL: {}\nError: {}",
            sql,
            errorMessage ? errorMessage : "Unknown");

        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

bool SQLiteActivityStorage::execute(Statement& stmt)
{
    if (sqlite3_step(stmt.get()) != SQLITE_DONE)
    {
        ChronosLogError(
            "SQLite execute failed: {}",
            sqlite3_errmsg(m_db));
        return false;
    }
    return true;
}

Statement SQLiteActivityStorage::prepare(std::string_view sql)
{
    assert(m_db != nullptr);

    sqlite3_stmt* stmt = nullptr;

    const int result = sqlite3_prepare_v2(
        m_db,
        sql.data(),
        static_cast<int>(sql.size()),
        &stmt,
        nullptr);

    if (result != SQLITE_OK)
    {
        ChronosLogError(
            "SQLite prepare failed.\nSQL: {}\nError: {}",
            sql,
            sqlite3_errmsg(m_db));

        return Statement(nullptr);
    }
    return Statement(stmt);
}