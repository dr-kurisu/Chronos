#pragma once
#include <Tag/Tag.h>
#include <optional>
#include <vector>

namespace chronos {
    class ITagStorage
    {
    public:
        virtual ~ITagStorage() = default;

        virtual TagId createTag(UserId, const Tag&) = 0;

        virtual std::vector<Tag> getAllTags(UserId ) = 0;

        virtual bool updateTag(UserId, const Tag&) = 0;

        virtual bool removeTag(UserId, TagId) = 0;

        virtual bool hasTag(UserId, TagId) = 0;

        virtual bool ensureBuiltinTags(UserId) = 0;
    };
}