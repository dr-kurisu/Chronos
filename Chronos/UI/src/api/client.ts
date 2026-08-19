const API_BASE_URL = "http://localhost:18080";

export async function apiFetch(
    path: string,
    options?: RequestInit
): Promise<Response> {
    return fetch(`${API_BASE_URL}${path}`, options);
}