#pragma once

#include <Core/Core.h>
#include <Activity/Activity.h>

namespace chronos {
    class IActivityStorage
    {
    public:
        virtual ~IActivityStorage() = default;

        // Activity
        virtual ActivityId insertActivity(const Activity&) = 0;
        virtual bool updateActivity(const Activity&) = 0;
        virtual bool removeActivity(ActivityId) = 0;

        // Query
        virtual std::vector<Activity> findActivities(
            UserId,
            Timestamp,
            Timestamp) = 0;
    };
}
