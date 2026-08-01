import TimelineBlock from "./TimelineBlock";
import { TimelineItem } from "../types";
import { TimelineStyles } from "./styles";

interface TimelineColumnProps {
    items: TimelineItem[];
    startHour: number;
    endHour: number;
    hourHeight: number;
}

function timeToPosition(
    time: string,
    startHour: number,
    hourHeight: number
) {
    const [hour, minute] =
        time.split(":")
            .map(Number);


    return (
        hour - startHour
        +
        minute / 60
    ) * hourHeight;
}



function calculateHeight(
    start: string,
    end: string,
    startHour: number,
    hourHeight: number
) {
    return (
        timeToPosition(
            end,
            startHour,
            hourHeight
        )
        -
        timeToPosition(
            start,
            startHour,
            hourHeight
        )
    );
}

export default function TimelineColumn({
    items,
    startHour,
    endHour,
    hourHeight
}: TimelineColumnProps) {


    const hours =
        Array.from(
            {
                length:
                    endHour - startHour + 1
            },
            (_, i) => startHour + i
        );


    return (

        <div
            className={TimelineStyles.column}
            style={{
                height:
                    (endHour - startHour)
                    *
                    hourHeight
            }}
        >


            {/* Timeline Lines */}

            {
                hours.map(hour => (

                    <div
                        key={hour}
                        className={TimelineStyles.gridLine}
                        style={{
                            top:(hour - startHour) * hourHeight
                        }}
                    />
                ))
            }

            {/* Blocks */}
            {
                items.map(item => (
                    <TimelineBlock
                        key={item.id}
                        item={item}
                        top={
                            timeToPosition(
                                item.start,
                                startHour,
                                hourHeight
                            )
                        }

                        height={
                            calculateHeight(
                                item.start,
                                item.end,
                                startHour,
                                hourHeight
                            )
                        }
                    />
                ))
            }
        </div>
    )

}