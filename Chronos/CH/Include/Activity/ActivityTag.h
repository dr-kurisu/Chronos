#pragma once
#include <Core/Core.h>

namespace chronos {
    enum class ActivityTags : uint32_t
    {
        None = 0,
        Browser = 1u << 0,
        Code = 1u << 1,
        Study = 1u << 2,
        Work = 1u << 3,
        Game = 1u << 4,
        Video = 1u << 5,
        Music = 1u << 6,
        Chat = 1u << 7,
        Social = 1u << 8,
        FileManager = 1u << 9,
        Terminal = 1u << 10,
        Trash = 1u << 11
    };

    constexpr ActivityTags operator|(ActivityTags lhs, ActivityTags rhs)
    {
        return static_cast<ActivityTags>(
            static_cast<uint32_t>(lhs) |
            static_cast<uint32_t>(rhs));
    }

    constexpr ActivityTags operator&(ActivityTags lhs, ActivityTags rhs)
    {
        return static_cast<ActivityTags>(
            static_cast<uint32_t>(lhs) &
            static_cast<uint32_t>(rhs));
    }

    constexpr ActivityTags operator~(ActivityTags value)
    {
        return static_cast<ActivityTags>(
            ~static_cast<uint32_t>(value));
    }

    constexpr ActivityTags& operator|=(ActivityTags& lhs, ActivityTags rhs)
    {
        lhs = static_cast<ActivityTags>(
            static_cast<uint32_t>(lhs) |
            static_cast<uint32_t>(rhs));
        return lhs;
    }

    constexpr ActivityTags& operator&=(ActivityTags& lhs, ActivityTags rhs)
    {
        lhs = static_cast<ActivityTags>(
            static_cast<uint32_t>(lhs) &
            static_cast<uint32_t>(rhs));
        return lhs;
    }

    constexpr void addTag(ActivityTags& tags, ActivityTags tag)
    {
        tags |= tag;
    }

    constexpr void removeTag(ActivityTags& tags, ActivityTags tag)
    {
        tags &= ~tag;
    }

    constexpr bool hasTag(ActivityTags tags, ActivityTags tag)
    {
        return (tags & tag) != ActivityTags::None;
    }
}
