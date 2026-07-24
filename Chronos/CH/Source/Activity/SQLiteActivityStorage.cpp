#include <Activity/SQLiteActivityStorage.h>
#include <Activity/Statement.h>
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

UserId chronos::SQLiteActivityStorage::createUser(const chronos::User& user)
{
    std::optional<User> existUser = findUserByName(user.name);
    if (existUser) {
        ChronosLogWarning("Username: {} already exist", existUser->name);
        return existUser->id;
    }

    constexpr std::string_view sql = R"(
        INSERT INTO Users
        (
            Name,
            PasswordHash,
            CreatedTime
        )
        VALUES
        (
            ?,
            ?,
            ?
        );
    )";
    Statement stmt = prepare(sql);
    if (!stmt)
        return -1;

    sqlite3_bind_text(stmt.get(), 1, user.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.get(), 2, user.passwordHash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt.get(), 3, user.createdTime);

    if (!execute(stmt))
        return -1;

    UserId id = static_cast<UserId>(
        sqlite3_last_insert_rowid(m_db));

    ChronosLogInfo(
        "Created user. Id: {}, Name: {}",
        id,
        user.name);
    return id;
}

void SQLiteActivityStorage::updateUser(const User& user)
{
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
        return;
    }

    sqlite3_bind_text(stmt.get(), 1, user.name.c_str(), - 1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.get(), 2, user.passwordHash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt.get(), 3, user.id);

    if (!execute(stmt))
        return;
    
    if (sqlite3_changes(m_db) == 0)
    {
        ChronosLogWarning("UserId: {} does not exist.", user.id);
    }
}

void SQLiteActivityStorage::removeUser(UserId id)
{
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
        return;
    }

    sqlite3_bind_int64(stmt.get(), 1, id);
    if (!execute(stmt))
        return;

    if (sqlite3_changes(m_db) == 0)
    {
        ChronosLogWarning("UserId: {} does not exist.", id);
    }
}

std::optional<User> SQLiteActivityStorage::findUser(UserId id)
{
    return std::optional<User>();
}

std::optional<User> chronos::SQLiteActivityStorage::findUserByName(std::string name)
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

std::vector<User> chronos::SQLiteActivityStorage::findAllUsers()
{
    return std::vector<User>();
}

ActivityId chronos::SQLiteActivityStorage::insertActivity(const Activity& activity)
{
    return ActivityId();
}

void chronos::SQLiteActivityStorage::updateActivity(const Activity& activity)
{

}

void chronos::SQLiteActivityStorage::removeActivity(ActivityId id)
{

}

std::optional<Activity> chronos::SQLiteActivityStorage::findActivity(ActivityId id)
{
    return std::optional<Activity>();
}

std::vector<Activity> chronos::SQLiteActivityStorage::findActivities(UserId userId)
{
    return std::vector<Activity>();
}

std::vector<Activity> chronos::SQLiteActivityStorage::findActivities(UserId userId, Timestamp begin, Timestamp end)
{
    return std::vector<Activity>();
}



bool chronos::SQLiteActivityStorage::createTables()
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

Statement SQLiteActivityStorage::prepareOrThrow(std::string_view sql)
{
    Statement stmt = prepare(sql);

    if (!stmt.get())
    {
        throw std::runtime_error(sqlite3_errmsg(m_db));
    }

    return stmt;
}