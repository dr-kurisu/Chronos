#pragma once

#include <string>
#include <string_view>

namespace chronos
{
    std::string WideToUtf8(std::wstring_view wide);

    std::wstring Utf8ToWide(std::string_view utf8);
}