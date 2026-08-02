import { ActivityTag } from "./ActivityTag";

export enum PlanStatus {
    Todo,
    InProgress,
    Done
}

export enum PlanPriority {
    P0,
    P1,
    P2,
    P3
}


export interface Plan
{
    id: number;
    title: string;
    description?: string;
    startTime?: string;
    endTime?: string;
    priority: PlanPriority;
    tags: ActivityTag[];
    createdAt: string;
    status: PlanStatus;
}