import { ActivityTag } from "../types/ActivityTag";
import { Plan, PlanState } from "../types/PlanTypes";

export const mockPlans: Plan[] = [
    {
        id: 1,
        title: "Implement Renderer",
        description: "Finish ray tracing renderer implementation",
        startTime: "09:00",
        endTime: "11:00",
        tags: [
            ActivityTag.Code,
            ActivityTag.Work
        ],
        createdAt: "2026-08-01T08:00:00",
        status: PlanState.Todo
    },

    {
        id: 2,
        title: "Read Research Paper",
        description: "Read computer vision related papers",
        startTime: "14:00",
        endTime: "15:30",
        tags: [
            ActivityTag.Study,
            ActivityTag.Browser
        ],
        createdAt: "2026-08-01T10:30:00",
        status: PlanState.Todo
    },

    {
        id: 3,
        title: "Workout",
        description: "Gym training session",
        startTime: "18:00",
        endTime: "19:00",
        tags: [
            ActivityTag.Work
        ],
        createdAt: "2026-08-01T12:00:00",
        status: PlanState.Todo
    },

    {
        id: 4,
        title: "Learn TypeScript",
        description: "Study advanced TypeScript patterns",
        startTime: "20:00",
        endTime: "21:30",
        tags: [
            ActivityTag.Code,
            ActivityTag.Study
        ],
        createdAt: "2026-08-01T15:00:00",
        status: PlanState.Todo
    }
];

export async function fetchPlans(
    date:Date
):Promise<Plan[]>
{
    await new Promise(
        r=>setTimeout(r,300)
    );

    return mockPlans;
}