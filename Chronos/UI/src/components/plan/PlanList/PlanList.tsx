import { Plan } from "../../../types/PlanTypes";
import PlanCard from "./PlanCard";

interface Props
{
    plans: Plan[];
}

export default function PlanList({
    plans
}:Props)
{
    return (
        <div>
            {
                plans.map(plan=>(
                    <PlanCard
                        key={plan.id}
                        plan={plan}
                    />
                ))
            }
        </div>
    );
}