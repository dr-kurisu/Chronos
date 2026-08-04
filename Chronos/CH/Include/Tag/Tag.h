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
        constexpr TagId Work = 1;
        constexpr TagId Study = 2;
        constexpr TagId Code = 3;
        constexpr TagId Browser = 4;
        constexpr TagId Chat = 5;
        constexpr TagId Video = 6;
        constexpr TagId Music = 7;
        constexpr TagId Game = 8;
        constexpr TagId Terminal = 9;
        constexpr TagId FileManager = 10;
    }
}