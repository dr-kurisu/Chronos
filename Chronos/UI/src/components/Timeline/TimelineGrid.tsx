import TimelineColumn from "./TimelineColumn";
import { TimelineItem, TimelineItemType } from "./types";
import { ActivityTag } from "../../types/ActivityTag";
import { TimelineStyles } from "./styles";

const START_HOUR = 6;
const END_HOUR = 22;
const HOUR_HEIGHT = 80;

interface Props 
{
    items: TimelineItem[]
}


export default function TimelineGrid({items}: Props) {
    const hours = Array.from( {length: END_HOUR - START_HOUR + 1}, (_, i) => START_HOUR + i);
    const plans =
        items.filter(
            item =>
                item.type === TimelineItemType.Plan
        );
    const activities =
        items.filter(
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