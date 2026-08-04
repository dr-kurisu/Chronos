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

        // Tags
		virtual bool addTags(ActivityId, std::vector<TagId>) = 0;
		virtual bool removeTag(ActivityId, TagId) = 0;

        // Query
        virtual std::vector<Activity> findActivities(
            UserId,
            Timestamp,
            Timestamp) = 0;

		virtual bool hasTag(UserId userId, TagId id) = 0;
		virtual std::vector<TagId> getAllTags(ActivityId activityId) = 0;
    };
}
