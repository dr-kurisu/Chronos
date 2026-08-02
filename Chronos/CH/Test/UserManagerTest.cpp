#include <gtest/gtest.h>
#include <User/UserManager.h>
#include <Storage/SQliteDatabase.h>
#include <Storage/SQLiteActivityStorage.h>

namespace chronos 
{
	class UserManagerTest : public ::testing::Test 
	{
	public:
		void SetUp() override {
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
			UserManagerDesc desc{
				.base = *m_logger,
				.storage = *m_storage
			};
			m_userManager = std::make_unique<UserManager>(desc);

			m_userManager->registerUser("Test", "234");
		}

	protected:
		UniquePtr<Logger> m_logger;
		RefPtr<SQLiteDatabase> m_db;
		UniquePtr<SQLiteActivityStorage> m_storage;
		UniquePtr<UserManager> m_userManager;
	};

	TEST_F(UserManagerTest, RegisterValidUser) 
	{
		auto result = m_userManager->registerUser("Alice", "123");
		ASSERT_TRUE(result);
	}

	TEST_F(UserManagerTest, RegisterExistUser)
	{
		auto result1 = m_userManager->registerUser("Alice", "123");
		ASSERT_TRUE(result1);
		auto result2 = m_userManager->registerUser("Alice", "345");
		ASSERT_FALSE(result2);
	}

	TEST_F(UserManagerTest, RegisterInvalidUser) 
	{
		auto result1 = m_userManager->registerUser("Alice", "");
		ASSERT_FALSE(result1);
		auto result2 = m_userManager->registerUser("", "342");
		ASSERT_FALSE(result2);
	}

	TEST_F(UserManagerTest, LoginAndLogout) 
	{
		auto result1 = m_userManager->login("Test", "234");
		ASSERT_TRUE(m_userManager->isLoggedIn());
		ASSERT_TRUE(result1);
		m_userManager->logout();
		ASSERT_FALSE(m_userManager->isLoggedIn());
	}

	TEST_F(UserManagerTest, FailLogin) 
	{
		auto result1 = m_userManager->login("Error", "234");
		ASSERT_FALSE(m_userManager->isLoggedIn());
		ASSERT_FALSE(result1);
	}
}