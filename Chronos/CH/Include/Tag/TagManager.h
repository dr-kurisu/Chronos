#pragma once
#include <Core/Base.h>
#include <Core/Core.h>
#include <Tag/Tag.h>

#include <unordered_map>
#include <optional>

namespace chronos
{
    class TagManager : public Base
    {
    public:
        explicit TagManager(const TagManagerDesc&);
        TagId createTag(Tag&);
        bool ensureBuiltinTags();
        bool updateTag(const Tag&);
        bool removeTag(const Tag&);
        
        void setCurrentUserId(UserId);
        std::optional<Tag> getTag(TagId) const;
        void updateTagMap();
        std::unordered_map<TagId, Tag> getTagMap();

    private:
        AuthContext& m_authContext;
        std::unordered_map<TagId, Tag> m_tagMap;
        ITagStorage& m_storage;
    };
}