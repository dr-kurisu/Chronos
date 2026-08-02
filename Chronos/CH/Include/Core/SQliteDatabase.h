#pragma once
#include <Core/Statement.h>
#include <Core/Base.h>
#include <sqlite3.h>
#include <string>
#include <filesystem>

namespace chronos 
{
    class SQLiteDatabase : public Base
    {
    public:
        SQLiteDatabase(const SQLiteDatabaseDesc& desc);
        ~SQLiteDatabase();

        sqlite3* handle() const;
        sqlite3* connection();
        void configureDatabase();
        bool execute(std::string_view sql);
        bool execute(Statement& stmt);
        Statement prepare(std::string_view sql);

    private:
        sqlite3* m_db{};
        std::filesystem::path storagePath = "";
    };
}

