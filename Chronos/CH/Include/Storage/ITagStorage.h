#pragma once
#include <Tag/Tag.h>
#include <optional>
#include <vector>

namespace chronos {
    class ITagStorage
    {
    public:
        virtual ~ITagStorage() = default;

        virtual TagId createTag(UserId userId, const Tag& tag) = 0;

        virtual std::optional<Tag> getTag(UserId userId, TagId id) = 0;

        virtual std::optional<Tag> getTagByName(UserId userId, std::string_view name) = 0;

        virtual std::vector<Tag> getAllTags(UserId userId) = 0;

        virtual bool updateTag(UserId userId, const Tag& tag) = 0;

        virtual bool removeTag(UserId userId, TagId id) = 0;

        virtual bool hasTag(UserId userId, TagId id) = 0;
    };
}