#pragma once
#include <Tag/Tag.h>
#include <vector>

namespace chronos 
{
    inline const std::vector<Tag> BuiltinTags{
        {
            .name = "Work",
            .colour = "#3B82F6",
            .description = "Work related activities",
            .builtin = true
        },
        {
            .name = "Study",
            .colour = "#10B981",
            .description = "Study and learning",
            .builtin = true
        },
        {
            .name = "Code",
            .colour = "#8B5CF6",
            .description = "Programming and development",
            .builtin = true
        },
        {
            .name = "Browser",
            .colour = "#F59E0B",
            .description = "Web browsing",
            .builtin = true
        },
        {
            .name = "Chat",
            .colour = "#06B6D4",
            .description = "Messaging and communication",
            .builtin = true
        },
        {
            .name = "Video",
            .colour = "#EF4444",
            .description = "Watching videos",
            .builtin = true
        },
        {
            .name = "Music",
            .colour = "#EC4899",
            .description = "Listening to music",
            .builtin = true
        },
        {
            .name = "Game",
            .colour = "#F97316",
            .description = "Gaming",
            .builtin = true
        },
        {
            .name = "Terminal",
            .colour = "#6B7280",
            .description = "Terminal and shell",
            .builtin = true
        },
        {
            .name = "File Manager",
            .colour = "#84CC16",
            .description = "File management",
            .builtin = true
        }
    };
}