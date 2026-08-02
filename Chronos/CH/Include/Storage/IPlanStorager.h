#pragma once

#include <Plan/Plan.h>
#include <User/User.h>
#include <optional>
#include <vector>

namespace chronos
{
    class IPlanStorage
    {
    public:
        virtual PlanId insert(const Plan&) = 0;
        virtual bool update(const Plan&) = 0;
        virtual bool remove(PlanId) = 0;

        virtual std::optional<Plan> find(PlanId) = 0;

        virtual std::vector<Plan> findByUser(
            UserId,
            Timestamp,
            Timestamp) = 0;
    };
}