import { TimelineItem , TimelineItemType } from "./types";
import { TimelineStyles } from "./styles";
import { tagNames, tagColours } from "../../types/ActivityTag";

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
        top: `${top+2}px`,
        height: `${height-4}px`
    }}
>

    <div className={TimelineStyles.blockHeader}>
        <div className={TimelineStyles.blockTitle}>
            {item.title}
        </div>
    </div>

    <div className={TimelineStyles.blockTime}>
        {item.start} - {item.end}
    </div>


    <div className={TimelineStyles.tags}>
        {
            item.tags.map(tag => (
                <span 
                    key={tag}             
                    className={`
                        ${TimelineStyles.tag}
                        ${tagColours[tag]}
                    `}>
                    {tagNames[tag]}
                </span>
            ))
        }
    </div>


    
</div>
);
}