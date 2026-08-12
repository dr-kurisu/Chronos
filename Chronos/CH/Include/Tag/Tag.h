#pragma once
#include <Core/Core.h>

namespace chronos {
    struct Tag
    {
        TagId id{ -1 };
        UserId userId{ -1 };
        std::string name;
        std::string colour;
        std::string description;
        bool builtin = false;

        bool isValid() const
        {
            return !name.empty() && !colour.empty();
		}
    };

    namespace BuiltinTagId
    {
        inline constexpr TagId Work = 1;
        inline constexpr TagId Study = 2;
        inline constexpr TagId Code = 3;
        inline constexpr TagId Browser = 4;
        inline constexpr TagId Chat = 5;
        inline constexpr TagId Video = 6;
        inline constexpr TagId Music = 7;
        inline constexpr TagId Game = 8;
        inline constexpr TagId Terminal = 9;
        inline constexpr TagId FileManager = 10;
    }
}