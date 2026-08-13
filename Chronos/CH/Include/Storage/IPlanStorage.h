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
        virtual ~IPlanStorage() = default;
        virtual PlanId insertPlan(const Plan&) = 0;
        virtual bool updatePlan(const Plan&) = 0;
        virtual bool removePlan(UserId, PlanId) = 0;

        virtual std::optional<Plan> findPlan(PlanId) = 0;

        virtual std::vector<Plan> findPlanByUser(
            UserId,
            Timestamp,
            Timestamp) = 0;

        virtual std::vector<Plan> findPlanByUser(UserId) = 0;
    };
}