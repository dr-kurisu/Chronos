import { TimelineItem, TimelineItemType } from "../components/Timeline/types";
import { ActivityTag } from "../types/ActivityTag";

const mockTimeline: TimelineItem[] = [
    {
        id: 1,
        title: "Implement Renderer",
        start: "09:00",
        end: "11:00",
        tags: [
            ActivityTag.Code
        ],
        type: TimelineItemType.Plan,
    },

    {
        id: 2,
        title: "Visual Studio",
        start: "09:20",
        end: "10:40",
        tags: [
            ActivityTag.Code
        ],
        type: TimelineItemType.Activity,
    },

    {
        id: 3,
        title: "Read Research Paper",
        start: "14:00",
        end: "15:30",
        tags: [
            ActivityTag.Study,
            ActivityTag.Browser
        ],
        type: TimelineItemType.Plan,
    },

    {
        id: 4,
        title: "Chrome - arxiv",
        start: "14:15",
        end: "15:10",
        tags: [
            ActivityTag.Study
        ],
        type: TimelineItemType.Activity,
    }
];

export async function fetchTimeline(
    date: Date
): Promise<TimelineItem[]> {
    console.log(
        "Fetching timeline:",
        date.toISOString()
    );
    await new Promise(
        resolve => setTimeout(resolve, 300)
    );
    return mockTimeline;
}