import {
    createContext,
    useContext,
    useEffect,
    useState,
    type ReactNode,
} from "react";
import { apiFetch } from "../api/client";

type AuthContextType = {
    loading: boolean;
    authenticated: boolean;
};

const AuthContext = createContext<AuthContextType | null>(null);

export function AuthProvider({ children }: { children: ReactNode })
{
    const [loading, setLoading] = useState(true);
    const [authenticated, setAuthenticated] = useState(false);

    useEffect(() =>
    {
        initialiseAuth();
    }, []);

    async function initialiseAuth()
    {
        try
        {
            let response = await apiFetch("/api/session");

            if (response.status === 401)
            {
                const loginResponse = await apiFetch(
                    "/api/auth/login",
                    {
                        method: "POST",
                        headers: {
                            "Content-Type": "application/json",
                        },
                        body: JSON.stringify({
                            username: "TestUsername",
                            password: "TestPassword",
                        }),
                    }
                );

                if (!loginResponse.ok)
                {
                    setAuthenticated(false);
                    return;
                }

                response = await apiFetch("/api/session");
            }

            setAuthenticated(response.ok);
        }
        catch
        {
            setAuthenticated(false);
        }
        finally
        {
            setLoading(false);
        }
    }

    return (
        <AuthContext.Provider
            value={{
                loading,
                authenticated,
            }}
        >
            {children}
        </AuthContext.Provider>
    );
}

export function useAuth()
{
    const context = useContext(AuthContext);

    if (!context)
    {
        throw new Error(
            "useAuth must be used inside AuthProvider"
        );
    }

    return context;
}