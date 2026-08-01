import {
    CalendarCheck,
    ChartNoAxesColumn,
    LayoutGrid,
    CalendarDays,
    Plus
} from "lucide-react";

import {
    PlanHeaderStyles
} from "./style";

interface PlanHeaderProps {
    activeView: PlanView;
    onViewChange: (view: PlanView) => void;
    onCreatePlan: () => void;
}

export type PlanView =
    | "list"
    | "kanban"
    | "calendar"
    | "analytics";


const views = [
    {
        id: "list",
        label: "List",
        icon: CalendarCheck,
    },
    {
        id: "kanban",
        label: "Kanban Board",
        icon: LayoutGrid,
    },
    {
        id: "calendar",
        label: "Calendar",
        icon: CalendarDays,
    },
    {
        id: "analytics",
        label: "Analytics",
        icon: ChartNoAxesColumn,
    },
] satisfies {
    id: PlanView;
    label: string;
    icon: React.ElementType;
}[];


export default function PlanHeader({
    activeView,
    onViewChange,
    onCreatePlan
}:PlanHeaderProps){

return (

<header className={PlanHeaderStyles.header}>

    <div className={PlanHeaderStyles.brand}>
        <div className={PlanHeaderStyles.logo}>
            <CalendarCheck
                size={28}
                className="text-purple-600"
            />
        </div>

        <h1 className={PlanHeaderStyles.title}>
            Plan
        </h1>
    </div>

    <nav className={PlanHeaderStyles.navigation}>
    {
        views.map(view=>{
            const Icon=view.icon;
            const active =
                activeView===view.id;
            return (
                <button 
                    key={view.id} 
                    onClick={ ()=> onViewChange(view.id) }
                    className={`
                        ${PlanHeaderStyles.navItem}
                        ${active
                            ? PlanHeaderStyles.navActive
                            : PlanHeaderStyles.navInactive
                        }
                    `}
                >
                    <Icon size={20}/>

                    {view.label}

                    {
                        active && <span className={PlanHeaderStyles.underline}/>
                    }
                </button>
            )

        })
    }

    </nav>
    
    <button
        className={PlanHeaderStyles.createButton}
        onClick={onCreatePlan}
    >
        <Plus size={20}/>
        New Plan
    </button>
</header>

)

}