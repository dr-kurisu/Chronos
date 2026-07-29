import type { ReactNode } from "react";
import Card from "../common/card";

interface StatCardProps {
    title: string;
    value: string;
    icon: ReactNode;
    trend?: string;
    trendPositive?: boolean;
    chart?: ReactNode;
}

export default function StatCard({
    title,
    value,
    icon,
    trend,
    trendPositive = true,
}: StatCardProps) {
    return (
        <Card className="relative">
            <div className="flex justify-between">

                <div>
                    {/* icon + title */}
                    <div className="flex items-center gap-3">
                        <div
                            className="
                            flex
                            h-12
                            w-12
                            items-center
                            justify-center
                            rounded-xl
                            bg-green-100
                            "
                        >
                            {icon}
                        </div>

                        <span className="font-semibold text-gray-700">
                            {title}
                        </span>
                    </div>


                    {/* value */}
                    <div className="mt-5">
                        <div className="text-4xl font-bold">
                            {value}
                        </div>

                        {trend && (
                            <div
                                className={`
                                mt-2
                                text-sm
                                ${trendPositive 
                                    ? "text-green-500"
                                    : "text-red-500"
                                }
                                `}
                            >
                                ↑ {trend}
                                <span className="text-gray-500">
                                    {" "}vs yesterday
                                </span>
                            </div>
                        )}
                    </div>

                </div>
            </div>
        </Card>
    );
}