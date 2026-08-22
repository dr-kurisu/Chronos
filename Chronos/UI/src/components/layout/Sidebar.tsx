import {
    Home,
    Clock,
    BarChart3,
    Settings,
    Sprout,
} from "lucide-react";

import { User } from "../../types/User";
import { fetchCurrentUser } from "../../api/user";
import { useState, useEffect } from "react";

import "./Sidebar.css";

const menuItems = [
    {
        name: "Dashboard",
        icon: Home,
        path: "/",
    },
    {
        name: "Plan",
        icon: Sprout,
        path: "/plan",
    },
    {
        name: "Timeline",
        icon: Clock,
        path: "/timeline",
    },
    {
        name: "Analytics",
        icon: BarChart3,
        path: "/analytics",
    },
    {
        name: "Settings",
        icon: Settings,
        path: "/settings",
    },
];

const DEFAULT_USER: User = {
    id: 99999999,
    username: "default",
    name: "Default",
    createdTime: 0,
};

export function useCurrentUser() {
    const [user, setUser] = useState<User | null>(null);
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        fetchCurrentUser()
            .then((user) => {
                setUser(user ?? DEFAULT_USER);
            })
            .catch(() => {
                setUser(DEFAULT_USER);
            })
            .finally(() => {
                setLoading(false);
            });
    }, []);

    return {
        user,
        loading,
    };
}

export default function Sidebar() {
    const { user, loading } = useCurrentUser();

    return (
        <aside className="sidebar">
            <div className="sidebar-logo">
                <div className="sidebar-logo-icon">
                    C
                </div>

                <span className="sidebar-logo-text">
                    Chronos
                </span>
            </div>

            <nav className="sidebar-menu">
                {menuItems.map((item) => {
                    const Icon = item.icon;

                    return (
                        <a
                            key={item.name}
                            href={item.path}
                            className="sidebar-menu-item"
                        >
                            <Icon size={20} />
                            <span>{item.name}</span>
                        </a>
                    );
                })}
            </nav>

            <div className="sidebar-user">
                <div className="sidebar-user-avatar">
                    {user?.name?.charAt(0).toUpperCase() ?? "?"}
                </div>

                <div className="sidebar-user-info">
                    {loading ? (
                        <span className="sidebar-user-loading">
                            Loading...
                        </span>
                    ) : (
                        <>
                            <span className="sidebar-user-name">
                                {user?.name ?? "Default"}
                            </span>

                            <span className="sidebar-user-id">
                                ID: {user?.id ?? 0}
                            </span>
                        </>
                    )}
                </div>
            </div>
        </aside>
    );
}