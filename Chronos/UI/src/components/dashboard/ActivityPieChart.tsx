import { Pie, PieChart, ResponsiveContainer, Sector } from "recharts";
import { ActivityStatistic } from "../../types/ActivityTypes";
import { ActivePieSectorDataItem } from "../../types/ActivityTypes";
import AnimatedSector from "./AnimatedSector";
import { useEffect, useState } from "react";

interface Props {
    data: ActivityStatistic[];
    activeIndex?: number;
    setActiveIndex: React.Dispatch<
        React.SetStateAction<number | undefined>
    >;
    isReady: boolean;
    setIsReady: React.Dispatch<React.SetStateAction<boolean>>;
}

export default function ActivityPieChart({ data, activeIndex, setActiveIndex, isReady, setIsReady }: Props) {
    const animationDuration = 300;
    useEffect(() => {
        const timer = setTimeout(() => {
            setIsReady(true);
        }, animationDuration);

        return () => clearTimeout(timer);
    }, []);
    return (
        <ResponsiveContainer width="100%" height="100%">
            <PieChart>
                <Pie
                    data={data}
                    dataKey="percentage"
                    outerRadius={80}
                    paddingAngle={1}
                    onMouseEnter={
                        isReady
                            ? (_, index) => setActiveIndex(index)
                            : undefined
                    }
                    onMouseLeave={
                        isReady
                            ? () => setActiveIndex(undefined)
                            : undefined
                    }
                    isAnimationActive
                    animationDuration={animationDuration}
                    animationEasing="ease-out"
                    shape={(props: ActivePieSectorDataItem) => {
                        const item = props.payload as ActivityStatistic;
                        return (
                            <AnimatedSector
                                {...props}
                                active={props.index === activeIndex}
                                colour={item.colour}
                            />
                        );
                    }}
                ></Pie>
            </PieChart>
        </ResponsiveContainer>
    );
}