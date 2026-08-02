#include <gtest/gtest.h>
#include <Activity/SQLiteActivityStorage.h>
#include <Core/SQliteDatabase.h>
#include <Core/Common.h>

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

            User user;
            user.name = "Test";
            user.passwordHash = "123";
            testUserId = m_storage->createUser(user);
        }

    protected:
        UniquePtr<Logger> m_logger;
        UniquePtr<SQLiteActivityStorage> m_storage;
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

    TEST_F(SQLiteActivityStorageTest, CreateUser)
    {
        // Create valid user
        User user;
        user.name = "Alice";
        user.passwordHash = "123";
        UserId id = m_storage->createUser(user);
        EXPECT_GT(id, 0);
    }

    TEST_F(SQLiteActivityStorageTest, CreateInvalidUser)
    {
        // Create invalid user with empty passwordHash
        User user{};
        user.name = "Invalid";
        user.passwordHash = "";
        UserId id = m_storage->createUser(user);
        EXPECT_EQ(id, -1);

        // Create invlaid user without name
        User user2{};
        user2.passwordHash = "123";
        UserId id2 = m_storage->createUser(user2);
        EXPECT_EQ(id2, -1);
    }

    TEST_F(SQLiteActivityStorageTest, FindUserByName)
    {
        // Find valid user
        User user;
        user.name = "Alice";
        user.passwordHash = "123";
        UserId id = m_storage->createUser(user);

        auto result = m_storage->findUserByName("Alice");
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result->id, id);
        EXPECT_EQ(result->name, user.name);
        EXPECT_EQ(result->passwordHash, user.passwordHash);
    }

    TEST_F(SQLiteActivityStorageTest, FindInvalidUserByName) 
    {
        // Find non-exist user
        auto result = m_storage->findUserByName("Alice");
        ASSERT_FALSE(result.has_value());
    }

    TEST_F(SQLiteActivityStorageTest, RemoveUser)
    {
        // Remove valid user
        User user;
        user.name = "Alice";
        user.passwordHash = "123";
        UserId id = m_storage->createUser(user);
        auto result = m_storage->removeUser(id);
        ASSERT_TRUE(result);
    }

    TEST_F(SQLiteActivityStorageTest, RemoveInvalidUser)
    {
        // Remove user without id
        auto result = m_storage->removeUser(-1);
        ASSERT_FALSE(result);
        // Remove user with non-exist id
        auto result2 = m_storage->removeUser(100);
        ASSERT_FALSE(result2);
    }

    TEST_F(SQLiteActivityStorageTest, UpdateUser)
    {
        // Update Valid User
        User user;
        user.name = "Alise";
        user.passwordHash = "123";
        UserId id = m_storage->createUser(user);

        User updatedUser;
        updatedUser.id = id;
        updatedUser.name = "Alice";
        updatedUser.passwordHash = "345";

        auto result = m_storage->updateUser(updatedUser);
        auto newUser = m_storage->findUserByName("Alice");
        ASSERT_TRUE(result);
        EXPECT_EQ(newUser->id, id);
        EXPECT_EQ(newUser->name, updatedUser.name);
        EXPECT_EQ(newUser->passwordHash, updatedUser.passwordHash);
    }

    TEST_F(SQLiteActivityStorageTest, UpdateInvalidUser)
    {
        User user1;
        user1.name = "Alise";
        user1.passwordHash = "123";
        UserId id = m_storage->createUser(user1);
        // Update User without id
        User user2;
        user2.name = "Alice";
        user2.passwordHash = "345";
        auto result1 = m_storage->updateUser(user2);
        ASSERT_FALSE(result1);

        // Update User with insufficient info
        User user3;
        user3.id = id;
        user3.name = "Alice";
        auto result2 = m_storage->updateUser(user3);
        ASSERT_FALSE(result2);

        // Update Non-exist user
        User user4;
        user4.id = 100;
        user4.name = "Alice";
        user4.passwordHash = "123";
        auto result3 = m_storage->updateUser(user4);
        ASSERT_FALSE(result3);
    }

    TEST_F(SQLiteActivityStorageTest, FindUser)
    {
        User user1;
        user1.name = "Alise";
        user1.passwordHash = "123";
        UserId id = m_storage->createUser(user1);
        auto result = m_storage->findUser(id);

        // Find valid user
        EXPECT_EQ(result->id, id);
        EXPECT_EQ(result->name, user1.name);
        EXPECT_EQ(result->passwordHash, user1.passwordHash);
    }

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