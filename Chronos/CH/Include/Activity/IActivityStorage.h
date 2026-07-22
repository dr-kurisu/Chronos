#pragma once

#include <Activity/Activity.h>

namespace chronos {
    class IActivityStorage
    {
    public:
        virtual ~IActivityStorage() = default;

        virtual void insert(const Activity&) = 0;
        virtual void update(const Activity&) = 0;
        virtual void remove(ActivityId) = 0;
    };
}
