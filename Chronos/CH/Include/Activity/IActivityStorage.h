#pragma once

#include <Core/Core.h>
#include <Activity/Activity.h>

namespace chronos {
    class IActivityStorage
    {
    public:
        virtual ~IActivityStorage() = default;

        // User
        virtual UserId createUser(const User&) = 0;
        virtual void updateUser(const User&) = 0;
        virtual void removeUser(UserId) = 0;

        // Activity
        virtual ActivityId insertActivity(const Activity&) = 0;
        virtual void updateActivity(const Activity&) = 0;
        virtual void removeActivity(ActivityId) = 0;

        // Query
        virtual std::optional<User> findUser(UserId) = 0;
        virtual std::vector<User> findAllUsers() = 0;
        virtual std::optional<Activity> findActivity(ActivityId) = 0;
        virtual std::vector<Activity> findActivities(
            UserId,
            Timestamp,
            Timestamp) = 0;
    };
}
