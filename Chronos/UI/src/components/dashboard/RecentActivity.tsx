import Card from "../common/Card";
import { Activity } from "../../types/ActivityTypes";

interface Props {
    activities: Activity[];
}

export default function RecentActivity({
    activities
}: Props) {

    return (
        <Card>
            <h2 className="text-lg font-semibold">
                Recent Activity
            </h2>

            <div className="mt-4 space-y-3">
                {
                    activities.slice(0, 5).map((activity) => (
                        <div
                            key={activity.id}
                            className="
                                flex items-center justify-between
                                rounded-lg px-3 py-2
                                hover:bg-gray-50
                                transition-colors
                            "
                        >
                            <div className="flex items-center gap-3">

                                <div
                                    className="
                                        w-3 h-3 rounded-full
                                        bg-blue-500
                                    "
                                />

                                <div>
                                    <p className="text-sm font-medium">
                                        {activity.window.processName}
                                    </p>

                                    <p className="text-xs text-gray-500 truncate max-w-52">
                                        {activity.window.title}
                                    </p>
                                </div>

                            </div>


                            <span className="text-xs text-gray-400">
                                {formatDuration(activity)}
                            </span>

                        </div>
                    ))
                }
            </div>
        </Card>
    );
}

function formatDuration(activity: Activity)
{
    const start = new Date(activity.startTime);
    const end = new Date(activity.endTime);

    const seconds =
        Math.floor(
            (end.getTime() - start.getTime()) / 1000
        );

    if (seconds < 60)
        return `${seconds}s`;

    const minutes = Math.floor(seconds / 60);

    if (minutes < 60)
        return `${minutes}m`;

    return `${Math.floor(minutes / 60)}h ${minutes % 60}m`;
}