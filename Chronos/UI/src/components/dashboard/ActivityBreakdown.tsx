import { tagNames } from "../../types/ActivityTag";
import { ActivityStatistic } from "../../types/ActivityTypes";
import ActivityPieChart from "./ActivityPieChart";
import Card from "../common/Card";
import { useRef } from "react";


interface Props {
    data: ActivityStatistic[];
    activeIndex?: number;
    setActiveIndex: React.Dispatch<
        React.SetStateAction<number | undefined>
    >;
    isReady: boolean;
    setIsReady: React.Dispatch<React.SetStateAction<boolean>>;
}


export default function ActivityBreakdown({ data, activeIndex, setActiveIndex, isReady, setIsReady }: Props) {
    const leaveTimer = useRef<number | null>(null);

    const handleLeave = () => {
        leaveTimer.current = window.setTimeout(() => {
            setActiveIndex(undefined);
        }, 50);
    };

    const handleEnter = (index: number) => {
        if (leaveTimer.current !== null) {
            clearTimeout(leaveTimer.current);
        }

        setActiveIndex(index);
    };
    return (
        <Card className="h-full">
            <h2 className="text-lg font-semibold">
                Activity Breakdown
            </h2>

            <div className="mt-6 flex items-center gap-8">
                <div className="h-64 w-64">
                    <ActivityPieChart 
                        data={data} 
                        activeIndex={activeIndex} 
                        setActiveIndex={setActiveIndex}
                        isReady={isReady}
                        setIsReady={setIsReady}
                    />
                </div>
                
                <div className="space-y-3">
                    {data.map((item, index) => (
                    <div
                        key={item.tag}
                        onMouseEnter={() => handleEnter(index)}
                        onMouseLeave={handleLeave}
                        className={`
                            flex w-40 items-center justify-between rounded-lg px-2 py-1
                            text-sm cursor-pointer transition-all duration-200
                            ${
                                activeIndex === index
                                    ? "bg-gray-100 shadow-sm"
                                    : "hover:bg-gray-50"
                            }
                        `}
                    >
                        <div className="flex items-center gap-2">
                            <span
                                className={`rounded-full transition-all duration-200 ${
                                    activeIndex === index
                                        ? "w-4 h-4"
                                        : "w-3 h-3"
                                }`}
                                style={{ backgroundColor: item.colour }}
                            />

                            <span
                                className={
                                    activeIndex === index
                                        ? "font-medium text-gray-900"
                                        : "text-gray-600"
                                }
                            >
                                {tagNames[item.tag]}
                            </span>
                        </div>
                        <span className="font-semibold">
                            {item.percentage}%
                        </span>
                    </div>
                    ))}
                </div>
            </div>
        </Card>
    );
}