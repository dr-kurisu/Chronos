import { Plan } from "../../../types/PlanTypes";
import { tagNames, tagColours } from "../../../types/ActivityTag";


interface Props {
    plan: Plan;
}


export default function PlanCard({
    plan
}: Props) {

    return (
        <div
            className="
                flex
                flex-col
                gap-2
                p-3
                rounded-lg
                border
                bg-white
                hover:bg-gray-50
                transition
            "
        >

            {/* Title */}
            <div
                className="
                    text-sm
                    font-medium
                    text-gray-800
                "
            >
                {plan.title}
            </div>


            {/* Time */}
            <div
                className="
                    text-xs
                    text-gray-500
                "
            >
                {plan.startTime} - {plan.endTime}
            </div>


            {/* Tags */}
            <div
                className="
                    flex
                    gap-1
                    flex-wrap
                "
            >
                {
                    plan.tags.map(tag => (
                        <span
                            key={tag}
                            className={`
                                text-xs
                                px-2
                                py-0.5
                                rounded-full
                                ${tagColours[tag]}
                            `}
                        >
                            {tagNames[tag]}
                        </span>
                    ))
                }
            </div>

        </div>
    );
}