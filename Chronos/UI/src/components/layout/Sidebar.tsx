import {
    Home,
    Clock,
    BarChart3,
    Settings,
    Sprout,
} from "lucide-react";


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


export default function Sidebar() {
    return (
        <aside
            className="
                h-screen
                w-64
                border-r
                bg-white
                px-4
                py-6
            "
        >
            {/* Logo */}
            <div className="mb-8 flex items-center gap-3 px-3">
                <div
                    className="
                        flex
                        h-10
                        w-10
                        items-center
                        justify-center
                        rounded-xl
                        bg-blue-500
                        text-white
                        font-bold
                    "
                >
                    C
                </div>

                <span className="text-xl font-semibold">
                    Chronos
                </span>
            </div>


            {/* Menu */}
            <nav className="space-y-2">
                {menuItems.map((item) => {
                    const Icon = item.icon;

                    return (
                        <a
                            key={item.name}
                            href={item.path}
                            className="
                                flex
                                items-center
                                gap-3
                                rounded-lg
                                px-3
                                py-2
                                text-gray-600
                                hover:bg-gray-100
                            "
                        >
                            <Icon size={20}/>

                            <span>
                                {item.name}
                            </span>
                        </a>
                    );
                })}
            </nav>
        </aside>
    );
}