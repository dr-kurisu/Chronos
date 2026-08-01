import { Plan } from "../types/PlanTypes";
import { Activity } from "../types/ActivityTypes";
import { TimelineItem, TimelineItemType } from "../components/Timeline/types";

export function planToTimelineItem(
    plan: Plan
): TimelineItem
{
    return {
        id: plan.id,
        title: plan.title,
        start: plan.startTime,
        end: plan.endTime,
        tags: plan.tags,
        type: TimelineItemType.Plan
    };
}


export function activityToTimelineItem(
    activity: Activity
): TimelineItem
{
    return {
        id: activity.id,
        title: activity.window.title,
        start: activity.startTime,
        end: activity.endTime,
        tags: activity.tags,
        type: TimelineItemType.Activity
    };
}