#pragma once
#include <Core/Core.h>
#include <Core/Base.h>
#include <Storage/ITagStorage.h>

namespace chronos 
{
	class SQLiteTagStorage : public Base, public ITagStorage {
	public:
		explicit SQLiteTagStorage(const SQLiteStorageDesc& desc);
        TagId createTag(UserId userId, const Tag& tag) override;
        std::vector<Tag> getAllTags(UserId userId) override;
        bool updateTag(UserId userId, const Tag& tag) override;
        bool removeTag(UserId userId, TagId id) override;
        bool hasTag(UserId userId, TagId id) override;
        bool ensureBuiltinTags(UserId userId) override;
    private:
        bool createTable();

    private:
        SQLiteDatabase& m_db;
	};
}