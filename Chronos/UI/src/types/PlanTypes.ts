import { ActivityTag } from "./ActivityTag";

export enum PlanState
{
    Todo = 0,
    Progress,
    Done,
}

export interface Plan
{
    id: number;
    title: string;
    description?: string;
    startTime: string;
    endTime: string;
    tags: ActivityTag[];
    createdAt: string;
    status: PlanState;
}