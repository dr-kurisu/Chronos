export const PlanHeaderStyles = {
    header: `
        w-full
        h-24
        bg-white
        border-b
        border-gray-100
        flex
        items-center
        px-8
        gap-10
    `,

    brand: `
        flex
        items-center
        gap-4
        min-w-fit
    `,

    logo: `
        w-12
        h-12
        rounded-xl
        bg-purple-50
        flex
        items-center
        justify-center
    `,

    title: `
        text-3xl
        font-semibold
        text-gray-900
    `,

    navigation: `
        flex
        items-center
        gap-2
        flex-1
        h-full
    `,

    navItem: `
        relative
        h-full
        px-5
        flex
        items-center
        gap-2
        text-sm
        font-medium
        transition
    `,

    navActive: `
        text-purple-600
    `,

    navInactive: `
        text-gray-500
        hover:text-gray-900
    `,

    underline: `
        absolute
        bottom-0
        left-4
        right-4
        h-0.5
        bg-purple-600
        rounded-full
    `,

    createButton: `
        flex
        items-center
        gap-2
        px-5
        py-3
        rounded-xl
        bg-purple-600
        text-white
        font-medium
        shadow-sm
        hover:bg-purple-700
        transition
    `
};