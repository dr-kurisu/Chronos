#include <Storage/SQLiteDatabase.h>
#include <Storage/SQLiteUserStorage.h>


using namespace chronos;

SQLiteUserStorage::SQLiteUserStorage(const SQLiteStorageDesc& desc):
	Base(desc.base), m_db(desc.db)
{
    if (!createTable())
    {
        ChronosLogError("Failed to create UserSQLite tables.");
    }
}

SQLiteUserStorage::~SQLiteUserStorage()
{
}

UserId SQLiteUserStorage::createUser(const User& user)
{
    constexpr std::string_view sql = R"(
        INSERT INTO Users
        (
            Name,
            PasswordHash,
            CreatedTime,
            Username
        )
        VALUES
        (?, ?, ?, ?);
    )";
    Statement stmt = m_db.prepare(sql);
    if (!stmt) return -1;


    sqlite3_bind_text(stmt.get(), 1, user.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.get(), 2, user.passwordHash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt.get(), 3, user.createdTime);
    sqlite3_bind_text(stmt.get(), 4, user.username.c_str(), -1, SQLITE_TRANSIENT);

    if (!m_db.execute(stmt))
        return -1;

    UserId id = static_cast<UserId>(
        sqlite3_last_insert_rowid(m_db.handle()));

    ChronosLogInfo(
        "Created user successfully.   Id: {}, Username: {}",
        id,
        user.username);
    return id;
}

bool SQLiteUserStorage::updateUser(const User& user)
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
            Username = ?
        WHERE
            Id = ?;
    )";

    Statement stmt = m_db.prepare(sql);
    if (!stmt)
    {
        ChronosLogError(
            "Failed to update user: {}",
            sqlite3_errmsg(m_db.handle()));
        return false;
    }

    sqlite3_bind_text(stmt.get(), 1, user.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.get(), 2, user.passwordHash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt.get(), 3, user.username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt.get(), 4, user.id);

    if (!m_db.execute(stmt)) return false;

    if (sqlite3_changes(m_db.handle()) == 0)
    {
        ChronosLogWarning("UserId: {} does not exist.", user.id);
        return false;
    }
    ChronosLogInfo("Successfully update user with Id: {}, Username: {}", user.id, user.username);
    return true;
}

bool SQLiteUserStorage::removeUser(UserId id)
{
    if (id < 0) {
        ChronosLogWarning("Failed to remove invalid userid.");
        return false;
    }
    constexpr std::string_view sql = R"(
        DELETE FROM Users
        WHERE Id = ?;
    )";

    Statement stmt = m_db.prepare(sql);
    if (!stmt)
    {
        ChronosLogError(
            "Failed to remove user: {}",
            sqlite3_errmsg(m_db.handle()));
        return false;
    }

    sqlite3_bind_int64(stmt.get(), 1, id);
    if (!m_db.execute(stmt))
        return false;

    if (sqlite3_changes(m_db.handle()) == 0)
    {
        ChronosLogWarning("UserId: {} does not exist.", id);
        return false;
    }
    return true;
}

std::optional<User> SQLiteUserStorage::findUser(UserId id)
{
    // check id
    if (id < 0) {
        ChronosLogWarning("Failed to findUser with invalid id");
        return std::nullopt;
    }
    constexpr std::string_view sql = R"(
        SELECT
            Id,
            Username,
            Name, 
            PasswordHash,
            CreatedTime
        FROM Users
        WHERE Id = ?;
    )";
    Statement stmt = m_db.prepare(sql);
    if (!stmt) return std::nullopt;
    sqlite3_bind_int64(stmt.get(), 1, id);

    const int result = sqlite3_step(stmt.get());
    if (result == SQLITE_ROW)
    {
        User user;
        user.id = static_cast<UserId>(
            sqlite3_column_int64(stmt.get(), 0));
        user.username = reinterpret_cast<const char*>(
            sqlite3_column_text(stmt.get(), 1));
        user.name = reinterpret_cast<const char*>(
            sqlite3_column_text(stmt.get(), 2));
        user.passwordHash = reinterpret_cast<const char*>(
            sqlite3_column_text(stmt.get(), 3));
        user.createdTime = static_cast<Timestamp>(
            sqlite3_column_int64(stmt.get(), 4));
        return user;
    }

    if (result != SQLITE_DONE)
    {
        ChronosLogError(
            "Failed to find user: {}",
            sqlite3_errmsg(m_db.handle()));
    }
    return std::nullopt;
}

std::optional<User> SQLiteUserStorage::findUserByUsername(std::string username)
{
    constexpr std::string_view sql = R"(
        SELECT
            Id,
            Username,
            Name,
            PasswordHash,
            CreatedTime
        FROM Users
        WHERE Username = ?;
    )";

    Statement stmt = m_db.prepare(sql);
    if (!stmt)
        return std::nullopt;

    sqlite3_bind_text(stmt.get(), 1, username.c_str(), -1, SQLITE_TRANSIENT);

    const int result = sqlite3_step(stmt.get());
    if (result == SQLITE_ROW)
    {
        User user;
        user.id = static_cast<UserId>(
            sqlite3_column_int64(stmt.get(), 0));
        user.username = reinterpret_cast<const char*>(
            sqlite3_column_text(stmt.get(), 1));
        user.name = reinterpret_cast<const char*>(
            sqlite3_column_text(stmt.get(), 2));
        user.passwordHash = reinterpret_cast<const char*>(
            sqlite3_column_text(stmt.get(), 3));
        user.createdTime = static_cast<Timestamp>(
            sqlite3_column_int64(stmt.get(), 4));
        return user;
    }

    if (result != SQLITE_DONE)
    {
        ChronosLogError(
            "Failed to find user by username: {}",
            sqlite3_errmsg(m_db.handle()));
    }

    return std::nullopt;
}

bool SQLiteUserStorage::createTable()
{
	bool success = true;
    // Create User Table
    success &= m_db.execute(R"(
        CREATE TABLE IF NOT EXISTS Users
        (
            Id           INTEGER PRIMARY KEY AUTOINCREMENT,
            Username     TEXT NOT NULL UNIQUE,
            Name         TEXT NOT NULL,
            PasswordHash TEXT NOT NULL,
            CreatedTime  INTEGER NOT NULL
        );
    )");

    return success;
}

