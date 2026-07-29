import type { ReactNode } from "react";

interface CardProps {
    title?: ReactNode;
    children: ReactNode;
    footer?: ReactNode;
    className?: string;
}

export default function Card({
    title,
    children,
    footer,
    className = "",
}: CardProps) {
    return (
        <div
            className={`rounded-xl border border-gray-200 bg-white shadow-sm ${className}`}
        >
            {title && (
                <div className="border-b px-6 py-4 font-semibold">
                    {title}
                </div>
            )}

            <div className="p-6">
                {children}
            </div>

            {footer && (
                <div className="border-t px-6 py-4">
                    {footer}
                </div>
            )}
        </div>
    );
}