import { User } from "../types/User";
import { apiFetch } from "./client";

export interface LoginRequest {
    username: string;
    password: string;
}

export interface RegisterRequest {
    username: string;
    password: string;
    name: string;
}

export async function fetchCurrentUser(): Promise<User> {
    const response = await apiFetch(
        "/api/user"
    );

    if (!response.ok) {
        throw new Error(
            `Failed to fetch current user: ${response.status}`
        );
    }

    return response.json();
}

export async function registerUser(
    username: string,
    password: string,
    name: string
): Promise<void> {
    const response = await fetch(
        "/api/auth/register",
        {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify({
                username,
                password,
                name
            }),
        }
    );

    if (!response.ok) {
        throw new Error(
            `Failed to register user: ${response.status}`
        );
    }
}

export async function login(
    username: string,
    password: string
): Promise<void> {
    const response = await fetch(
        "/api/auth/login",
        {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify({
                username,
                password,
            }),
        }
    );

    if (!response.ok) {
        throw new Error(
            `Failed to login: ${response.status}`
        );
    }
}

export async function logout(): Promise<void> {
    const response = await fetch(
        "/api/auth/logout",
        {
            method: "POST",
        }
    );

    if (!response.ok) {
        throw new Error(
            `Failed to logout: ${response.status}`
        );
    }
}

