#include <Storage/SQLitePlanStorage.h>
#include <Storage/SQLiteDatabase.h>

using namespace chronos;

SQLitePlanStorage::SQLitePlanStorage(const SQLiteStorageDesc& desc) :
	Base(desc.base), m_db(desc.db)
{
	if (!createTable())
	{
		ChronosLogError("Failed to create PlanSQLite tables.");
	}
}

SQLitePlanStorage::~SQLitePlanStorage()
{
}

PlanId SQLitePlanStorage::insertPlan(const Plan& plan)
{
	constexpr std::string_view sql = R"(
		INSERT INTO Plans
		(
			UserId,
			Title,
			Description,
			StartTime,
			EndTime,
			Priority
		)
		VALUES
		(?, ?, ?, ?, ?, ?);
	)";

	Statement stmt = m_db.prepare(sql);
	if (!stmt)
	{
		ChronosLogError("Failed to prepare statement for inserting plan.");
		return -1;
	}
	// bind params
	sqlite3_bind_int(stmt.get(), 1, plan.userId);
	sqlite3_bind_text(stmt.get(), 2, plan.title.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt.get(), 3, plan.description.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt.get(), 4, plan.convertTimePoint(plan.startTime));
	sqlite3_bind_int64(stmt.get(), 5, plan.convertTimePoint(plan.endTime));
	sqlite3_bind_int(stmt.get(), 6, static_cast<int>(plan.priority));

	// execute
	if (!m_db.execute(stmt)) return -1;
	PlanId id = static_cast<PlanId>(sqlite3_last_insert_rowid(m_db.handle()));
	ChronosLogInfo("Create Plan successfully.   Plan id: {}", id);
	return id;
}

bool SQLitePlanStorage::updatePlan(const Plan& plan)
{
	constexpr std::string_view sql = R"(
        UPDATE Plans
        SET
            Title = ?,
            Description = ?,
            StartTime = ?,
            EndTime = ?,
            Priority = ?
        WHERE Id = ? AND
		UserId = ?;
    )";

	Statement stmt = m_db.prepare(sql);
	if (!stmt)
	{
		ChronosLogError("Failed to prepare update plan.");
		return false;
	}
	sqlite3_bind_text(stmt.get(), 1,
		plan.title.c_str(), -1, SQLITE_TRANSIENT);

	sqlite3_bind_text(stmt.get(), 2,
		plan.description.c_str(), -1, SQLITE_TRANSIENT);

	sqlite3_bind_int64(stmt.get(), 3,
		plan.convertTimePoint(plan.startTime));

	sqlite3_bind_int64(stmt.get(), 4,
		plan.convertTimePoint(plan.endTime));

	sqlite3_bind_int(stmt.get(), 5,
		static_cast<int>(plan.priority));

	sqlite3_bind_int64(stmt.get(), 6,
		plan.id);

	sqlite3_bind_int64(stmt.get(), 7,
		plan.userId);

	return m_db.execute(stmt);
}

bool SQLitePlanStorage::removePlan(UserId userId, PlanId id)
{
	constexpr std::string_view sql = R"(
        DELETE FROM Plans
        WHERE Id = ? AND
		UserId = ?;
    )";
	Statement stmt = m_db.prepare(sql);
	if (!stmt)
	{
		ChronosLogError("Failed to prepare delete plan.");
		return false;
	}
	sqlite3_bind_int64(stmt.get(), 1, id);
	sqlite3_bind_int64(stmt.get(), 2, userId);
	if (!m_db.execute(stmt))
		return false;
	return sqlite3_changes(m_db.handle()) > 0;
}

std::optional<Plan> SQLitePlanStorage::findPlan(PlanId id)
{
	constexpr std::string_view sql = R"(
        SELECT
            Id,
            UserId,
            Title,
            Description,
            StartTime,
            EndTime,
            Priority
        FROM Plans
        WHERE Id = ?;
    )";

	Statement stmt = m_db.prepare(sql);
	if (!stmt)
		return std::nullopt;
	sqlite3_bind_int64(stmt.get(), 1, id);

	if (sqlite3_step(stmt.get()) != SQLITE_ROW)
		return std::nullopt;

	auto plan = readPlan(stmt.get());
	return plan;
}

std::vector<Plan> SQLitePlanStorage::findPlanByUser(UserId id)
{
	constexpr std::string_view sql = R"(
        SELECT
            Id,
            UserId,
            Title,
            Description,
            StartTime,
            EndTime,
            Priority
        FROM Plans
        WHERE UserId = ?
        ORDER BY StartTime;
    )";


	std::vector<Plan> plans;


	Statement stmt = m_db.prepare(sql);

	if (!stmt)
		return plans;


	sqlite3_bind_int64(stmt.get(), 1, id);


	while (sqlite3_step(stmt.get()) == SQLITE_ROW)
	{
		auto plan = readPlan(stmt.get());
		if (plan) plans.push_back(*plan);
	}
	return plans;
}

std::vector<Plan> SQLitePlanStorage::findPlanByUser(
	UserId id,
	Timestamp start,
	Timestamp end)
{
	constexpr std::string_view sql = R"(
        SELECT
            Id,
            UserId,
            Title,
            Description,
            StartTime,
            EndTime,
            Priority
        FROM Plans
        WHERE UserId = ?
        AND StartTime < ?
        AND EndTime > ?
        ORDER BY StartTime;
    )";

	std::vector<Plan> plans;

	Statement stmt = m_db.prepare(sql);

	if (!stmt)
		return plans;


	sqlite3_bind_int64(stmt.get(), 1, id);
	sqlite3_bind_int64(stmt.get(), 2, end);
	sqlite3_bind_int64(stmt.get(), 3, start);


	while (sqlite3_step(stmt.get()) == SQLITE_ROW)
	{
		auto plan = readPlan(stmt.get());
		if (plan) plans.push_back(*plan);
	}
	return plans;
}

bool SQLitePlanStorage::createTable() 
{
	// Need modify
	bool success = true;
	success &= m_db.execute(R"(
		CREATE TABLE IF NOT EXISTS Plans
		(
			Id           INTEGER PRIMARY KEY AUTOINCREMENT,
			UserId       INTEGER NOT NULL,
			Title		 TEXT NOT NULL,
			Description  TEXT,
			StartTime	 INTEGER NOT NULL,
			EndTime		 INTEGER NOT NULL,
			Priority     INTEGER NOT NULL,
			FOREIGN KEY(UserId) REFERENCES Users(Id) ON DELETE CASCADE
		);
	)");

	success &= m_db.execute(R"( 
        CREATE INDEX IF NOT EXISTS idx_plans_user
        ON Plans(UserId);
    )");

	// PlanTags
	success &= m_db.execute(R"(
        CREATE TABLE IF NOT EXISTS PlanTags
        (
            PlanId INTEGER NOT NULL,
            TagId      INTEGER NOT NULL,
            PRIMARY KEY(PlanId, TagId),
            FOREIGN KEY(PlanId) REFERENCES Plans(Id) ON DELETE CASCADE,
            FOREIGN KEY(TagId) REFERENCES Tags(Id) ON DELETE CASCADE
        );
    )");

	success &= m_db.execute(R"(
        CREATE INDEX IF NOT EXISTS idx_plan_tags_tag
        ON PlanTags(TagId);
    )");

	return success;
}

std::optional<Plan> SQLitePlanStorage::readPlan(sqlite3_stmt* stmt)
{
    if (!stmt)
        return std::nullopt;

    Plan plan;

    plan.id = sqlite3_column_int64(stmt,0);

    plan.userId = sqlite3_column_int(stmt,1);

    plan.title = reinterpret_cast<const char*>(
        sqlite3_column_text(stmt,2));

    const char* desc = reinterpret_cast<const char*>(
        sqlite3_column_text(stmt,3));

    if(desc)
        plan.description = desc;

    plan.startTime = plan.convertTimestamp(
        sqlite3_column_int64(stmt,4));


    plan.endTime = plan.convertTimestamp(
        sqlite3_column_int64(stmt,5));


    plan.priority = static_cast<PlanPriority>(
        sqlite3_column_int(stmt,6));


    return plan;
}
