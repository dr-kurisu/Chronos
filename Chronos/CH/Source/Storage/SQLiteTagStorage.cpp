#include <Storage/SQLiteTagStorage.h>
#include <Storage/SQLiteDatabase.h>

using namespace chronos;

SQLiteTagStorage::SQLiteTagStorage(const SQLiteStorageDesc& desc):
	Base(desc.base), m_db(desc.db)
{
	if (!createTable())
	{
		ChronosLogError("Failed to create PlanSQLite tables.");
	}
	ChronosLogInfo("PlanDatabase initialised");
}

TagId SQLiteTagStorage::createTag(UserId userId, const Tag& tag)
{
	// check tag
	if (!tag.isValid()) 
	{
		ChronosLogWarning("Fail to insert invalid tag.");
		return -1;
	}

	constexpr std::string_view sql = R"(
		INSERT INTO Tags
		(
			UserId,
			Name,
			Colour,
			Description,
			Builtin
		)
		VALUES
		(?, ?, ?, ?, ?);
	)";

	Statement stmt = m_db.prepare(sql);
	if (!stmt)
	{
		ChronosLogError("Failed to prepare statement for creating tag.");
		return -1;
	}

	// Bind parameters
	sqlite3_bind_int64(stmt.get(), 1, tag.userId);
	sqlite3_bind_text(stmt.get(), 2, tag.name.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt.get(), 3, tag.colour.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt.get(), 4, tag.description.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt.get(), 5, tag.builtin ? 1 : 0);

	// Execute
	if (!m_db.execute(stmt))
	{
		ChronosLogError("Failed to execute statement for creating tag.");
		return -1;
	}

	TagId id = static_cast<TagId>(sqlite3_last_insert_rowid(m_db.handle()));
	return id;
}

std::vector<Tag> SQLiteTagStorage::getAllTags(UserId userId)
{
	std::vector<Tag> tags;
	constexpr std::string_view sql = R"(
		SELECT
			Id,
			Name,
			Colour,
			Description,
			Builtin
		FROM Tags
		WHERE UserId = ?;
	)";
	Statement stmt = m_db.prepare(sql);
	if (!stmt)
	{
		ChronosLogError("Failed to prepare statement for retrieving tags.");
		return tags;
	}
	sqlite3_bind_int64(stmt.get(), 1, userId);
	while (sqlite3_step(stmt.get()) == SQLITE_ROW)
	{
		Tag tag;
		tag.id = sqlite3_column_int64(stmt.get(), 0);
		tag.userId = userId;
		tag.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 1));
		tag.colour = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 2));
		tag.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 3));
		tag.builtin = sqlite3_column_int(stmt.get(), 4) != 0;
		tags.push_back(std::move(tag));
	}
	return tags;
}

bool SQLiteTagStorage::updateTag(UserId userId, const Tag& tag)
{
	// Check tag
	if (!tag.isValid() || tag.id < 0)
	{
		ChronosLogWarning("Failed to update invalid tag.");
		return false;
	}
	constexpr std::string_view sql = R"(
		UPDATE Tags
		SET
			Name = ?,
			Colour = ?,
			Description = ?,
			Builtin = ?
		WHERE
			Id = ? AND UserId = ?;
	)";
	Statement stmt = m_db.prepare(sql);
	if (!stmt)
	{
		ChronosLogError("Failed to prepare statement for updating tag.");
		return false;
	}
	sqlite3_bind_text(stmt.get(), 1, tag.name.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt.get(), 2, tag.colour.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt.get(), 3, tag.description.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt.get(), 4, tag.builtin ? 1 : 0);
	sqlite3_bind_int64(stmt.get(), 5, tag.id);
	sqlite3_bind_int64(stmt.get(), 6, userId);

	if (!m_db.execute(stmt)) return false;

	if (sqlite3_changes(m_db.handle()) == 0)
	{
		ChronosLogWarning(
			"No tag updated (Id={}, UserId={}).",
			tag.id,
			userId);
		return false;
	}
	return true;
}

bool SQLiteTagStorage::removeTag(UserId userId, TagId id)
{
	// Check params
	if (userId < 0 || id < 0)
	{
		ChronosLogWarning("Failed to removeTag with invalid params");
		return false;
	}
	constexpr std::string_view sql = R"(
		DELETE FROM Tags
		WHERE Id = ? AND UserId = ?;
	)";
	Statement stmt = m_db.prepare(sql);
	if (!stmt) return false;
	sqlite3_bind_int64(stmt.get(), 1, id);
	sqlite3_bind_int64(stmt.get(), 2, userId);
	if (!m_db.execute(stmt)) return false;
	if (sqlite3_changes(m_db.handle()) == 0)
	{
		ChronosLogWarning(
			"Fail to remove TagId: {} with UserId: {}.",
			id,
			userId);
		return false;
	}
	return true;
}

bool SQLiteTagStorage::hasTag(UserId userId, TagId id)
{
	// Check params
	if (userId < 0 || id < 0)
	{
		ChronosLogWarning("Failed to hasTag with invalid params");
		return false;
	}
	constexpr std::string_view sql = R"(
		SELECT 1
		FROM Tags
		WHERE UserId = ? AND Id = ?
		LIMIT 1;
	)";
	Statement stmt = m_db.prepare(sql);
	if (!stmt) return false;
	sqlite3_bind_int64(stmt.get(), 1, userId);
	sqlite3_bind_int64(stmt.get(), 2, id);
	const int result = sqlite3_step(stmt.get());
	return result == SQLITE_ROW;
}

bool SQLiteTagStorage::createTable()
{
	auto success = m_db.execute(R"(
		CREATE TABLE IF NOT EXIST Tags
		(
			Id           INTEGER PRIMARY KEY AUTOINCREMENT,
			Name		 TEXT NOT NULL,
			Colour		 TEXT NOT NULL,
			Description  TEXT,
			Builtin      INTEGER NOT NULL,
		)
	)");

	return success;
}
