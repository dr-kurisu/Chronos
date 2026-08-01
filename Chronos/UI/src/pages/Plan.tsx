import { useEffect, useState } from "react";
import PlanHeader, { PlanView } from "../components/plan/PlanHeader/PlanHeader";
import TimeToolbar from "../components/Timeline/TimeToolbar/TimeToolbar";
import PlanList from "../components/plan/PlanList/PlanList";
import { Plan } from "../types/PlanTypes";
import { fetchPlans } from "../services/PlanApi";

function renderView(view: PlanView, plans: Plan[])
{
    switch(view)
    {
        case "list": return <PlanList plans={plans}/>;
        case "kanban": return null;
        default: return <PlanList plans={plans}/>;
    }
}

export default function Plan() 
{
    const [view,setView] = useState<PlanView>("list");
    const [date,setDate] = useState<Date>(new Date());
    const [plans,setPlans] = useState<Plan[]>([]);

    useEffect(()=>{
        fetchPlans(date)
            .then(data=>{
                setPlans(data);
            });

    },[date]);
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
            {renderView(view, plans)}
        </div>
    );
}