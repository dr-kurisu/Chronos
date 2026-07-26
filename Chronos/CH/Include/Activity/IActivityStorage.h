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
        virtual bool updateUser(const User&) = 0;
        virtual bool removeUser(UserId) = 0;

        // Activity
        virtual ActivityId insertActivity(const Activity&) = 0;
        virtual bool updateActivity(const Activity&) = 0;
        virtual bool removeActivity(ActivityId) = 0;

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
