#pragma once

#include <gtest/gtest.h>
#include <Activity/SQLiteActivityStorage.h>
#include <Core/Common.h>


namespace chronos {
    class SQLiteActivityStorageTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            m_logger = std::make_unique<Logger>(Logger::LogLevel::Info);
            SQLiteACStorageDesc SQLiteDesc{
                .base = *m_logger,
                .storagePath = ":memory:"
            };

            m_storage = std::make_unique<SQLiteActivityStorage>(SQLiteDesc);
        }

    protected:
        std::unique_ptr<Logger> m_logger;
        std::unique_ptr<SQLiteActivityStorage> m_storage;
    };

    TEST_F(SQLiteActivityStorageTest, CreateUser)
    {
        User user;
        user.name = "Alice";
        user.passwordHash = "123";
        UserId id = m_storage->createUser(user);
        EXPECT_GT(id, 0);
    }
}

