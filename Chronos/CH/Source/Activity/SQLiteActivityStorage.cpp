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
}

SQLiteActivityStorage::~SQLiteActivityStorage()
{
    if (m_db)
    {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
}

ActivityId SQLiteActivityStorage::insert(Activity& activity)
{
    return ActivityId();
}

void SQLiteActivityStorage::update(const Activity& activity)
{
}

void SQLiteActivityStorage::remove(ActivityId id)
{
}

std::optional<Activity> chronos::SQLiteActivityStorage::find(ActivityId id)
{
    return std::optional<Activity>();
}

std::vector<Activity> chronos::SQLiteActivityStorage::findAll()
{
    return std::vector<Activity>();
}

void SQLiteActivityStorage::configureDatabase()
{
    execute("PRAGMA foreign_keys = ON;");
}


bool chronos::SQLiteActivityStorage::createTables()
{
    return false;
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