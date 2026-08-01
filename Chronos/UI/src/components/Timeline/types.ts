import { ActivityTag } from "../../types/ActivityTag";

export enum TimelineItemType 
{
    Plan = 0,
    Activity,
}

export interface TimelineItem 
{
    id: number;
    title: string;
    start: string;
    end: string;
    tag: ActivityTag;
    type: TimelineItemType;
}
