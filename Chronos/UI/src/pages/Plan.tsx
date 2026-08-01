import { useState } from "react";
import PlanHeader, { PlanView } from "../components/plan/PlanHeader/PlanHeader";
import TimeToolbar from "../components/plan/TimeToolbar/TimeToolbar";
import PlanList from "../components/plan/PlanList/PlanList";

function renderView(view: PlanView)
{
    switch(view)
    {
        case "list": return <PlanList />;
        case "kanban": return null;
        default: return <PlanList />;
    }
}

export default function Plan() {
    const [view,setView] = useState<PlanView>("list");
    const [date,setDate] = useState<Date>(new Date());

    return (
        <div>
            <PlanHeader
                activeView={view}
                onViewChange={setView}
                onCreatePlan={() => {
                    console.log("create plan");
                }}
            />
            <TimeToolbar 
                date={date}
                onDateChange={setDate}
                onFilterChange={() => {
                    console.log("open filter");
                }}
            />
            {renderView(view)}
        </div>
    );
}