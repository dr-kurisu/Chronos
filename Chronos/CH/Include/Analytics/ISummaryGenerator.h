#pragma once

#include <Analytics/Summary.h>

namespace chronos 
{
    class ISummaryGenerator
    {
    public:
        virtual ~ISummaryGenerator() = default;

        virtual std::string generate(const Summary& summary) = 0;
    };
}
