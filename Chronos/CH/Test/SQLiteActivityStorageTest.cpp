#include <Core/Common.h>
#include <Storage/SQliteDatabase.h>
#include <Storage/SQLiteActivityStorage.h>
#include <Storage/SQLiteUserStorage.h>
#include <gtest/gtest.h>

namespace chronos {
    class SQLiteActivityStorageTest : public ::testing::Test
    {
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

            m_storage = std::make_unique<SQLiteActivityStorage>(SQLiteDesc);
            m_userStorage = std::make_unique<SQLiteUserStorage>(SQLiteDesc);

            User user;
            user.name = "Test";
            user.passwordHash = "123";
            testUserId = m_userStorage->createUser(user);
        }

    protected:
        UniquePtr<Logger> m_logger;
        UniquePtr<SQLiteActivityStorage> m_storage;
        UniquePtr<SQLiteUserStorage> m_userStorage;
        RefPtr<SQLiteDatabase> m_db;

        UserId testUserId;
        WindowInfo exampleWindow{
            .hwnd = reinterpret_cast<HWND>(0x00123456),
            .pid = 12345,
            .title = "code.cpp",
            .processName = "code.exe"
        };
    public:
        Logger& getLogger() const noexcept
        {
            return *m_logger;
        }
    };

    TEST_F(SQLiteActivityStorageTest, FindInvalidUser)
    {

    }

    TEST_F(SQLiteActivityStorageTest, InsertValidActivity)
    {
        Activity ac(exampleWindow);
        ac.userId = testUserId;
        auto result = m_storage->insertActivity(ac);
        EXPECT_GT(result, 0);
    }

    TEST_F(SQLiteActivityStorageTest, InsertInvalidActivity)
    {
        // Activity without window title
        WindowInfo exampleWindow2 = exampleWindow;
        exampleWindow2.title = "";
        Activity ac(exampleWindow2);
        auto result1 = m_storage->insertActivity(ac);
        EXPECT_EQ(result1, -1);

        // Activity with invalid window pid
        WindowInfo exampleWindow3 = exampleWindow;
        exampleWindow3.pid = 0;
        Activity ac1(exampleWindow3);
        auto result2 = m_storage->insertActivity(ac1);
        EXPECT_EQ(result2, -1);

        // To be continued ...
    }

    TEST_F(SQLiteActivityStorageTest, UpdateValidActivity)
    {

    }

    TEST_F(SQLiteActivityStorageTest, UpdateInValidActivity)
    {

    }

    TEST_F(SQLiteActivityStorageTest, findActivitiesValidActivities)
    {

    }

    TEST_F(SQLiteActivityStorageTest, findActivitiesInvalidActivities)
    {

    }
}