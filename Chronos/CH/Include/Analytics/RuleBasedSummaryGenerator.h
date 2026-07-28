#pragma once

#include <Analytics/ISummaryGenerator.h>

namespace chronos 
{
    class RuleBasedSummaryGenerator : public ISummaryGenerator
    {
    public:
        std::string generate(const Summary& summary) override
        {
            return "Rule based summary text generator example text.";
        }
    };
}