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

    enum class BuiltinTagId
    {
        Work,
        Study,
        Code,
        Browser,
        Chat,
        Video,
        Music,
        Game,
        Terminal,
        FileManager
    };
}