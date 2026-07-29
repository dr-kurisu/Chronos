import StatCard from "../components/dashboard/StatCard";
import {
    Clock3,
    Activity,
    Target,
} from "lucide-react";

interface DashboardStatistics {
    activeTime: string;
    activityCount: number;
    focusTime: string;
    activeTimeTrend: string;
    activityCountTrend: string;
    focusTimeTrend: string;
}

// fake data
const statistics: DashboardStatistics = {
    activeTime: "2h 35m",
    activeTimeTrend: "11%",
    activityCount: 128,
    activityCountTrend: "12%",
    focusTime: "1h 12m",
    focusTimeTrend: "42%",
};

export default function Dashboard() {
return (
        <div className="grid grid-cols-3 gap-6">
            <StatCard
                title="Active Time"
                value={statistics.activeTime}
                icon={<Clock3 size={24} />}
                trend={statistics.activeTimeTrend}
            />

            <StatCard
                title="Activities"
                value={statistics.activityCount.toString()}
                icon={<Activity size={24} />}
                trend={statistics.activityCountTrend}
            />

            <StatCard
                title="Focus Time"
                value={statistics.focusTime}
                icon={<Target size={24} />}
                trend={statistics.focusTimeTrend}
            />
        </div>
    );
}