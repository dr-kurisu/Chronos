#include <gtest/gtest.h>
#include <Core/Common.h>
#include <Storage/SQLiteTagStorage.h>
#include <Storage/SQLiteUserStorage.h>

namespace chronos {
    class SQLiteTagStorageTest : public ::testing::Test
    {
    public:
        Logger& getLogger() const noexcept
        {
            return *m_logger;
        }
    protected:
        void SetUp() override
        {
            m_logger = std::make_unique<Logger>(Logger::LogLevel::Error);
            m_db = std::make_shared<SQLiteDatabase>(SQLiteDatabaseDesc{
                .base = *m_logger,
                .storagePath = ":memory:"
				});
            SQLiteStorageDesc SQLiteDesc{
                .base = *m_logger,
                .db = *m_db
            };

			m_storage = std::make_unique<SQLiteTagStorage>(SQLiteDesc);
            m_userStorage = std::make_unique<SQLiteUserStorage>(SQLiteDesc);
            User user;
            user.name = "Test";
            user.passwordHash = "123";
            testUserId = m_userStorage->createUser(user);
        }

    protected:
        UniquePtr<Logger> m_logger;
        UniquePtr<SQLiteTagStorage> m_storage;
        UniquePtr<SQLiteUserStorage> m_userStorage;
        RefPtr<SQLiteDatabase> m_db;
        UserId testUserId;
    };

    TEST_F(SQLiteTagStorageTest, InsertValidTag) 
    {
        TagId id = m_storage->createTag(testUserId, Tag{
			.userId = testUserId,
            .name = "TestTag",
            .colour = "#FF0000",
            .description = "This is a test tag.",
            .builtin = false
		    }
        );
        EXPECT_GT(id, 0);
    }

    TEST_F(SQLiteTagStorageTest, InsertInvalidTag)
    {

    }

    TEST_F(SQLiteTagStorageTest, InsertValidTag)
    {

    }
}