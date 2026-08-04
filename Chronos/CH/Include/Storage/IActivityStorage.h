#pragma once

#include <Core/Core.h>
#include <Activity/Activity.h>
#include <span>

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
		virtual bool addTags(ActivityId, std::span<const TagId>) = 0;
        bool addTags(ActivityId id, std::initializer_list<TagId> tags) 
        {
            return addTags(id, std::span<const TagId>(tags.begin(), tags.size()));
        }
		virtual bool removeTag(ActivityId, TagId) = 0;

        // Query
        virtual std::vector<Activity> findActivities(
            UserId,
            Timestamp,
            Timestamp) = 0;

		virtual bool hasTag(ActivityId id, TagId tagId) = 0;
		virtual std::vector<TagId> getAllTags(ActivityId activityId) = 0;
    };
}
