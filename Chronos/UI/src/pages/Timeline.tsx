import TimelineGrid from "../components/Timeline/TimelineGrid";
import TimeToolbar from "../components/plan/TimeToolbar/TimeToolbar";
import { useState } from "react";

export default function Timeline() 
{
    const [date,setDate] = useState<Date>(new Date());
    return(
        <div>
            <TimeToolbar
                date={date}
                onDateChange={setDate}
                onFilterChange={() => {
                    console.log("open filter");
                } } 
            />
            <TimelineGrid />
        </div>
    );
}