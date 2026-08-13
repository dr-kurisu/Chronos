#include <Storage/SQliteDatabase.h>
#include <assert.h>

using namespace chronos;

SQLiteDatabase::SQLiteDatabase(const SQLiteDatabaseDesc& desc): 
    Base(desc.base), storagePath(desc.storagePath)
{
    connection();
}

SQLiteDatabase::~SQLiteDatabase()
{
    if (m_db)
    {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
}

sqlite3* SQLiteDatabase::handle() const
{
    return m_db;
}

void SQLiteDatabase::connection()
{
    //ChronosLogInfo("Working directory: {}",
    //    std::filesystem::current_path().string());

    //ChronosLogInfo("Database path: {}",
    //    storagePath.string());
    const int result = sqlite3_open(storagePath.string().c_str(), &m_db);
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
}

void chronos::SQLiteDatabase::configureDatabase()
{
    execute("PRAGMA foreign_keys = ON;");
}

bool SQLiteDatabase::execute(std::string_view sql)
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


bool SQLiteDatabase::execute(Statement & stmt)
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

Statement SQLiteDatabase::prepare(std::string_view sql)
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