import { apiFetch } from "./client";


export interface ActiveTimeResponse {
    duration: number;
}

export async function fetchActiveTime(): Promise<number> {
    const response = await apiFetch(
        "/api/activity/activetime"
    );

    if (!response.ok) {
        throw new Error(
            `Failed to fetch active time: ${response.status}`
        );
    }

    const data: ActiveTimeResponse = await response.json();
    return data.duration;
}