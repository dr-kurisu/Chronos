import { PieSectorDataItem } from "recharts";
import { ActivityTag } from "./ActivityTag"

export interface Activity {
    id: number;
    window: {
        title: string;
        processName: string;
    };
    startTime: string;
    endTime: string;
    tags: ActivityTag[];
}

export interface ActivityStatistic {
    tag: ActivityTag;
    percentage: number;
    colour: string;
}

export type ActivePieSectorDataItem = PieSectorDataItem & {
    isActive: boolean;
    index: number;
};