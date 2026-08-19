cmake_minimum_required(VERSION 3.25)

project(Chronos
    VERSION 0.1.0
    LANGUAGES CXX
)

option(CHRONOS_BUILD_TESTS "Build Chronos unit tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(VS_DEBUGGER_WORKING_DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(Crow CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(unofficial-webview2 CONFIG REQUIRED)
find_package(unofficial-argon2 CONFIG REQUIRED)

set(CHRONOS_CORE_SOURCES
    CH/Source/Activity/ActivityClassifier.cpp
    CH/Source/Activity/ActivityManager.cpp
    CH/Source/Activity/ActivityUtils.cpp
    CH/Source/Analytics/ActivitySummary.cpp
    CH/Source/Application/Application.cpp
    CH/Source/Application/Win32/Win32Application.cpp
    CH/Source/Core/Base.cpp
    CH/Source/Core/Logger.cpp
    CH/Source/Core/SQLiteDatabase.cpp
    CH/Source/Core/StringEncoding.cpp
    CH/Source/Monitor/Monitor.cpp
    CH/Source/Monitor/Windows/WindowsWatcher.cpp
    CH/Source/Plan/PlanManager.cpp
    CH/Source/Storage/SQLiteActivityStorage.cpp
    CH/Source/Storage/SQLitePlanStorage.cpp
    CH/Source/Storage/SQLiteTagStorage.cpp
    CH/Source/Storage/SQLiteUserStorage.cpp
    CH/Source/Tag/TagManager.cpp
    CH/Source/User/UserManager.cpp
    CH/Source/Window/Window.cpp
    CH/Source/Backend/Backend.cpp
    CH/Source/WebView/WebViewController.cpp
    CH/Source/Window/Window.cpp
    CH/Source/Backend/ActivityController.cpp
)


add_library(chronos_core STATIC
    ${CHRONOS_CORE_SOURCES}
)

target_compile_features(chronos_core PUBLIC
    cxx_std_20
)

target_compile_definitions(chronos_core PUBLIC
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    UNICODE
    _UNICODE
)

target_compile_options(chronos_core PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>
)

target_include_directories(chronos_core PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/CH/Include"
)

target_link_libraries(chronos_core PUBLIC
    unofficial::sqlite3::sqlite3
    unofficial::webview2::webview2
    unofficial::argon2::libargon2
    Crow::Crow
    bcrypt
)

add_executable(Chronos
    App/Main.cpp
)

target_link_libraries(Chronos PRIVATE
    chronos_core
)

set_target_properties(Chronos PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/Bin/$<CONFIG>"
    VS_DEBUGGER_WORKING_DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

if(CHRONOS_BUILD_TESTS)

    enable_testing()

    add_executable(ChronosTests
        App/TestMain.cpp
        CH/Test/SQLiteActivityStorageTest.cpp
        CH/Test/SQLiteTagStorageTest.cpp
        CH/Test/SQLiteUserStorageTest.cpp
        CH/Test/UserManagerTest.cpp
    )

    target_link_libraries(ChronosTests PRIVATE
        chronos_core
        GTest::gtest
        GTest::gtest_main
    )

    set_target_properties(ChronosTests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
            "${CMAKE_BINARY_DIR}/Bin/$<CONFIG>"
    )

    include(GoogleTest)
    gtest_discover_tests(ChronosTests)

endif()