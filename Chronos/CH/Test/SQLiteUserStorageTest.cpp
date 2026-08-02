#include <Core/Common.h>
#include <Storage/SQliteDatabase.h>
#include <Storage/SQLiteActivityStorage.h>
#include <Storage/SQLiteUserStorage.h>
#include <gtest/gtest.h>

namespace chronos {
    class SQLiteUserStorageTest : public ::testing::Test
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

            m_acStorage = std::make_unique<SQLiteActivityStorage>(SQLiteDesc);
            m_userStorage = std::make_unique<SQLiteUserStorage>(SQLiteDesc);

            User user;
            user.name = "Test";
            user.passwordHash = "123";
            testUserId = m_userStorage->createUser(user);
        }

    protected:
        UniquePtr<Logger> m_logger;
        UniquePtr<SQLiteActivityStorage> m_acStorage;
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

    TEST_F(SQLiteUserStorageTest, CreateUser)
    {
        // Create valid user
        User user;
        user.name = "Alice";
        user.passwordHash = "123";
        UserId id = m_userStorage->createUser(user);
        EXPECT_GT(id, 0);
    }

    TEST_F(SQLiteUserStorageTest, CreateInvalidUser)
    {
        // Create invalid user with empty passwordHash
        User user{};
        user.name = "Invalid";
        user.passwordHash = "";
        UserId id = m_userStorage->createUser(user);
        EXPECT_EQ(id, -1);

        // Create invlaid user without name
        User user2{};
        user2.passwordHash = "123";
        UserId id2 = m_userStorage->createUser(user2);
        EXPECT_EQ(id2, -1);
    }

    TEST_F(SQLiteUserStorageTest, FindUserByName)
    {
        // Find valid user
        User user;
        user.name = "Alice";
        user.passwordHash = "123";
        UserId id = m_userStorage->createUser(user);

        auto result = m_userStorage->findUserByName("Alice");
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result->id, id);
        EXPECT_EQ(result->name, user.name);
        EXPECT_EQ(result->passwordHash, user.passwordHash);
    }

    TEST_F(SQLiteUserStorageTest, FindInvalidUserByName)
    {
        // Find non-exist user
        auto result = m_userStorage->findUserByName("Alice");
        ASSERT_FALSE(result.has_value());
    }

    TEST_F(SQLiteUserStorageTest, RemoveUser)
    {
        // Remove valid user
        User user;
        user.name = "Alice";
        user.passwordHash = "123";
        UserId id = m_userStorage->createUser(user);
        auto result = m_userStorage->removeUser(id);
        ASSERT_TRUE(result);
    }

    TEST_F(SQLiteUserStorageTest, RemoveInvalidUser)
    {
        // Remove user without id
        auto result = m_userStorage->removeUser(-1);
        ASSERT_FALSE(result);
        // Remove user with non-exist id
        auto result2 = m_userStorage->removeUser(100);
        ASSERT_FALSE(result2);
    }

    TEST_F(SQLiteUserStorageTest, UpdateUser)
    {
        // Update Valid User
        User user;
        user.name = "Alise";
        user.passwordHash = "123";
        UserId id = m_userStorage->createUser(user);

        User updatedUser;
        updatedUser.id = id;
        updatedUser.name = "Alice";
        updatedUser.passwordHash = "345";

        auto result = m_userStorage->updateUser(updatedUser);
        auto newUser = m_userStorage->findUserByName("Alice");
        ASSERT_TRUE(result);
        EXPECT_EQ(newUser->id, id);
        EXPECT_EQ(newUser->name, updatedUser.name);
        EXPECT_EQ(newUser->passwordHash, updatedUser.passwordHash);
    }

    TEST_F(SQLiteUserStorageTest, UpdateInvalidUser)
    {
        User user1;
        user1.name = "Alise";
        user1.passwordHash = "123";
        UserId id = m_userStorage->createUser(user1);
        // Update User without id
        User user2;
        user2.name = "Alice";
        user2.passwordHash = "345";
        auto result1 = m_userStorage->updateUser(user2);
        ASSERT_FALSE(result1);

        // Update User with insufficient info
        User user3;
        user3.id = id;
        user3.name = "Alice";
        auto result2 = m_userStorage->updateUser(user3);
        ASSERT_FALSE(result2);

        // Update Non-exist user
        User user4;
        user4.id = 100;
        user4.name = "Alice";
        user4.passwordHash = "123";
        auto result3 = m_userStorage->updateUser(user4);
        ASSERT_FALSE(result3);
    }

    TEST_F(SQLiteUserStorageTest, FindUser)
    {
        User user1;
        user1.name = "Alise";
        user1.passwordHash = "123";
        UserId id = m_userStorage->createUser(user1);
        auto result = m_userStorage->findUser(id);

        // Find valid user
        EXPECT_EQ(result->id, id);
        EXPECT_EQ(result->name, user1.name);
        EXPECT_EQ(result->passwordHash, user1.passwordHash);
    }

    TEST_F(SQLiteUserStorageTest, FindInvalidUser)
    {

    }
}