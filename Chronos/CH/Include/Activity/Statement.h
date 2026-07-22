#pragma once
#include <sqlite3.h>

namespace chronos {
    class Statement
    {
    public:
        explicit Statement(sqlite3_stmt* stmt)
            : m_stmt(stmt)
        {
        }

        ~Statement()
        {
            if (m_stmt)
            {
                sqlite3_finalize(m_stmt);
            }
        }

        sqlite3_stmt* get() const
        {
            return m_stmt;
        }

    private:
        sqlite3_stmt* m_stmt{};
    };
}
