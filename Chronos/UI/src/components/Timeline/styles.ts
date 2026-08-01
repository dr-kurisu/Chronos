export const TimelineStyles = {
    block: `
        absolute
        left-1
        right-1
        flex
        flex-col
        justify-center
        px-3
        rounded-lg
        overflow-hidden
    `,


    planBlock: `
        bg-purple-100
        text-purple-700
    `,


    activityBlock: `
        bg-blue-100
        text-blue-700
    `,


    blockTitle: `
        font-medium
    `,


    blockTime: `
        text-xs
        opacity-70
    `,


    gridContainer: `
        w-full
        bg-white
        rounded-xl
        border
        overflow-hidden
    `,


    gridHeader: `
        grid
        grid-cols-[80px_1fr_1fr]
        h-14
        border-b
        items-center
        text-sm
        font-medium
        text-gray-600
    `,


    column: `
        relative
        border-l
    `,


    gridLine: `
        absolute
        left-0
        right-0
        border-b
    `,

        container: `
        w-full
        bg-white
        rounded-xl
        border
        overflow-hidden
    `,


    // Header

    header: `
        grid
        grid-cols-[80px_1fr_1fr]
        h-14
        border-b
        items-center
        text-sm
        font-medium
        text-gray-600
    `,


    headerCell: `
        px-4
    `,


    headerDividerCell: `
        px-4
        border-l
    `,

        blockHeader: `
        flex
        items-center
        gap-2
    `,


    tags: `
        flex
        items-center
        gap-1
        mt-1
        overflow-hidden
        whitespace-nowrap
    `,


    tag: `
        flex-shrink-0
        text-xs
        px-2
        py-0.5
        rounded-full
        bg-white/60
    `,


    // Body

    body: `
        grid
        grid-cols-[80px_1fr_1fr]
    `,


    // Time Column

    timeCell: `
        h-20
        border-b
        px-3
        pt-2
        text-xs
        text-gray-400
    `
};