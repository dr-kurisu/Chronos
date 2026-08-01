import TimelineColumn from "./TimelineColumn";
import { TimelineItem, TimelineItemType } from "./types";
import { ActivityTag } from "../../types/ActivityTag";
import { TimelineStyles } from "./styles";

const START_HOUR = 0;
const END_HOUR = 24;
const HOUR_HEIGHT = 80;


const mockItems: TimelineItem[] = [
    {
        id: 1,
        title: "Implement Renderer",
        start: "09:00",
        end: "11:00",
        tag: ActivityTag.Code,
        type: TimelineItemType.Plan,
    },
    {
        id: 2,
        title: "Visual Studio",
        start: "09:20",
        end: "10:40",
        tag: ActivityTag.Code,
        type: TimelineItemType.Activity,
    },
    {
        id: 3,
        title: "Read Research Paper",
        start: "14:00",
        end: "15:30",
        tag: ActivityTag.Study,
        type: TimelineItemType.Plan,
    },
    {
        id: 4,
        title: "Chrome - arxiv",
        start: "14:15",
        end: "15:10",
        tag: ActivityTag.Study,
        type: TimelineItemType.Activity,
    }
];


export default function TimelineGrid() {
    const hours = Array.from( {length: END_HOUR - START_HOUR + 1}, (_, i) => START_HOUR + i);
    const plans =
        mockItems.filter(
            item =>
                item.type === TimelineItemType.Plan
        );
    const activities =
        mockItems.filter(
            item =>
                item.type === TimelineItemType.Activity
        );

    return (
        <div className={TimelineStyles.container}>
            {/* Header */}
            <div className={TimelineStyles.header}>
                <div className={TimelineStyles.headerCell}>
                    Time
                </div>
                <div className={TimelineStyles.headerDividerCell}>
                    Plan
                </div>

                <div className={TimelineStyles.headerDividerCell}>
                    Activity
                </div>
            </div>

            {/* Body */}
            <div className={TimelineStyles.body}
            >
                {/* Time */}
                <div>
                    {
                        hours.map(hour => (
                            <div
                                key={hour}
                                className={TimelineStyles.timeCell}
                            >
                                {hour}:00
                            </div>
                        ))
                    }
                </div>

                {/* Plan */}
                <TimelineColumn
                    items={plans}
                    startHour={START_HOUR}
                    endHour={END_HOUR}
                    hourHeight={HOUR_HEIGHT}
                />

                {/* Activity */}
                <TimelineColumn
                    items={activities}
                    startHour={START_HOUR}
                    endHour={END_HOUR}
                    hourHeight={HOUR_HEIGHT}
                />
            </div>
        </div>
    )
}