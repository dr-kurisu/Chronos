import StatCard from "../components/dashboard/StatCard";
import ActivityBreakdown from "../components/dashboard/ActivityBreakdown";
import RecentActivity from "../components/dashboard/RecentActivity";
import { ActivityTag } from "../types/ActivityTag";

import { Clock3, Activity, Target } from "lucide-react";
import { useState } from "react";


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

const activityBreakdownData = [
    {
        tag: ActivityTag.Code,
        percentage: 35,
        colour: "#60a5fa",
    },
    {
        tag: ActivityTag.Browser,
        percentage: 25,
        colour: "#8b5cf6",
    },
    {
        tag: ActivityTag.Work,
        percentage: 20,
        colour: "#34d399",
    },
    {
        tag: ActivityTag.Video,
        percentage: 10,
        colour: "#fbbf24",
    },
    {
        tag: ActivityTag.Chat,
        percentage: 10,
        colour: "#f87171",
    },
];

const recentActivities = [
    {
        id: 1,
        window:{
            processName:"Code.exe",
            title:"Activity.cpp"
        },
        startTime:"2026-07-30T10:30:00",
        endTime:"2026-07-30T10:50:00",
        tags: [ActivityTag.Code]
    },
    {
        id:2,
        window:{
            processName:"chrome.exe",
            title:"GitHub"
        },
        startTime:"2026-07-30T10:45:00",
        endTime:"2026-07-30T11:00:00",
        tags: [ActivityTag.Code]
    }
];

export default function Dashboard() {
    const [activeIndex, setActiveIndex] = useState<number | undefined>();
    const [isReady, setIsReady] = useState(false);
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

            <ActivityBreakdown 
                data={activityBreakdownData}
                activeIndex={activeIndex}
                setActiveIndex={setActiveIndex}
                isReady={isReady}
                setIsReady={setIsReady}
            />

            <RecentActivity 
                activities={recentActivities}
            />

        </div>
    );
}