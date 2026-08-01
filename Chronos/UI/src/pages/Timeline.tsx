import TimelineGrid from "../components/Timeline/TimelineGrid";
import TimeToolbar from "../components/Timeline/TimeToolbar/TimeToolbar";
import { TimelineItem } from "../components/Timeline/types";
import { useEffect, useState } from "react";
import { fetchTimeline } from "../services/timelineAPI";

export default function Timeline() 
{
    const [date,setDate] = useState<Date>(new Date());
    const [items,setItems] = useState<TimelineItem[]>([]);
    useEffect(()=>{
        fetchTimeline(date)
            .then(data=>{
                setItems(data);
            });
    },[date]);
    return(
        <div>
            <TimeToolbar
                date={date}
                onDateChange={setDate}
                onFilterChange={() => {
                    console.log("open filter");
                } } 
            />
            <TimelineGrid items={items}/>
        </div>
    );
}