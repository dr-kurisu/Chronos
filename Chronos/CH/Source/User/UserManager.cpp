#include <User/UserManager.h>
#include <Activity/IActivityStorage.h>
#include <argon2.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")

using namespace chronos;

UserManager::UserManager(const UserManagerDesc& desc) : m_storage(desc.storage), Base(desc.base)
{
	// Create TestUser
	registerUser("TestUser", "TestPassword");
}

bool UserManager::registerUser(const std::string& username, const std::string& password)
{
	// Check username and password
	if (username.empty() || password.empty()) 
	{
		ChronosLogWarning("Fail to register User due to invalid username or password");
		return false;
	}
	User newUser;
	newUser.name = username;
	newUser.passwordHash = hashPassword(password);
	newUser.id = m_storage.createUser(newUser);
	return newUser.id >= 0;
}

bool UserManager::login(const std::string& username, const std::string& password)
{
    auto user = m_storage.findUserByName(username);
    if (!user)
    {
        return false;
    }

    if (!verifyPassword(password, user->passwordHash)) return false;

    m_currentUser = *user;
    return true;
}

void UserManager::logout()
{
	ChronosLogInfo("Logging out...");
	m_currentUser = std::nullopt;
}

bool UserManager::isLoggedIn() const
{
	return m_currentUser.has_value();
}

std::optional<User> UserManager::getCurrentUser() const
{
	return m_currentUser;
}

UserId UserManager::getCurrentUserId() const
{
	if (m_currentUser.has_value()) 
	{
		return m_currentUser->id;
	}else 
	{
		return -1;
	}
}

std::array<uint8_t, 16> UserManager::generateSalt() const
{
	std::array<uint8_t, 16> salt;

	BCryptGenRandom(
		nullptr,
		salt.data(),
		static_cast<ULONG>(salt.size()),
		BCRYPT_USE_SYSTEM_PREFERRED_RNG);

	return salt;
}

bool UserManager::verifyPassword(const std::string& password, const std::string& passwordHash)
{
	return argon2id_verify(passwordHash.c_str(), password.data(), password.size()) == ARGON2_OK;
}

std::string UserManager::hashPassword(const std::string& password) const
{
	constexpr uint32_t t_cost = 3;          // iterations
	constexpr uint32_t m_cost = 65536;      // 64 MB
	constexpr uint32_t parallelism = 1;
	constexpr size_t hashLen = 32;

	auto salt = generateSalt();

	char encoded[256];

	int result = argon2id_hash_encoded(
		t_cost,
		m_cost,
		parallelism,
		password.data(),
		password.size(),
		salt.data(),
		salt.size(),
		hashLen,
		encoded,
		sizeof(encoded));

	if (result != ARGON2_OK)
		throw std::runtime_error(argon2_error_message(result));

	return std::string(encoded);
}
