import { TimelineItem , TimelineItemType } from "./types";
import { TimelineStyles } from "./styles";

interface TimelineBlockProps 
{
    item: TimelineItem;
    top: number;
    height: number;
}

export default function TimelineBlock({ item, top, height }: TimelineBlockProps) 
{
return (
<div
    className={`
        ${TimelineStyles.block}
        ${
            item.type === TimelineItemType.Plan
            ? "bg-purple-100 text-purple-700"
            : "bg-blue-100 text-blue-700"
        }
    `}
    style={{
        top: `${top}px`,
        height: `${height}px`
    }}
>

    <div className={TimelineStyles.blockTitle}>
        {item.title}
    </div>

    <div className={TimelineStyles.blockTime}>
        {item.start} - {item.end}
    </div>
    
</div>
);
}