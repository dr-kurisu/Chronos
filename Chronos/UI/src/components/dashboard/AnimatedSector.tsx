import { useEffect, useRef, useState } from "react";
import { Sector } from "recharts";
import type { PieSectorDataItem } from "recharts/types/polar/Pie";

interface AnimatedSectorProps extends PieSectorDataItem {
    active: boolean;
    colour: string;
}

export default function AnimatedSector({
    active,
    colour,
    ...props
}: AnimatedSectorProps) {
    const [radius, setRadius] = useState(props.outerRadius ?? 80);
    const frame = useRef<number | null>(null);

    useEffect(() => {
        const target = active ? 90 : 80;

        const animate = () => {
            setRadius((current) => {
                const diff = target - current;

                if (Math.abs(diff) < 0.1) {
                    return target;
                }

                return current + diff * 0.05;
            });

            frame.current = requestAnimationFrame(animate);
        };

        frame.current = requestAnimationFrame(animate);

        return () => {
            if (frame.current) {
                cancelAnimationFrame(frame.current);
            }
        };
    }, [active]);

    return (
        <Sector
            {...props}
            fill={colour}
            outerRadius={radius}
        />
    );
}