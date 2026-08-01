import { ChevronLeft, ChevronRight, CalendarDays, Filter } from "lucide-react";
import { toolbarStyles } from "./styles";

interface Props {
    date: Date;
    onDateChange: (date: Date) => void;
    onFilterChange: () => void;
}

export default function TimeToolbar({
    date,
    onDateChange,
    onFilterChange
}: Props) {
    const previousDay = () => {
        const d = new Date(date);
        d.setDate(d.getDate() - 1);
        onDateChange(d);
    };


    const nextDay = () => {
        const d = new Date(date);
        d.setDate(d.getDate() + 1);
        onDateChange(d);
    };


    const today = () => {
        onDateChange(new Date());
    };

    return (
        <div className={toolbarStyles.container}>
            {/* left */}
            <div className={toolbarStyles.leftGroup}>

                <button onClick={previousDay}>
                    <ChevronLeft className={toolbarStyles.icon} />
                </button>


                <button className={toolbarStyles.dateButton}>
                    <CalendarDays className="w-5 h-5" />

                    {date.toLocaleDateString(
                        "en-US",
                        {
                            month: "short",
                            day: "numeric",
                            year: "numeric",
                            weekday: "short"
                        }
                    )}

                </button>

                <button onClick={nextDay}>
                    <ChevronRight className={toolbarStyles.icon} />
                </button>


                <button
                    onClick={today}
                    className={toolbarStyles.todayButton}
                >
                    Today
                </button>

            </div>
            {/* right */}
            <div className="flex gap-3">
                <button
                    onClick={onFilterChange}
                    className={toolbarStyles.actionButton}
                >
                    <Filter className="w-5 h-5" />
                    Filters
                </button>
            </div>
        </div>
    )
}