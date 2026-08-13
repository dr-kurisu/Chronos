set(CHRONOS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CH")
set(CHRONOS_THIRD_PARTY_DIR "${CHRONOS_SOURCE_DIR}/ThirdParty")
set(CHRONOS_WEBVIEW2_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/../packages/Microsoft.Web.WebView2.1.0.4129.50/build/native")

option(CHRONOS_BUILD_TESTS "Build Chronos unit tests" ON)

# Visual Studio's CMake folder-mode debugger reads this CMake variable when it
# determines the default working directory.  The target property below keeps
# the same behavior for generated Visual Studio projects.
set(VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(CHRONOS_CORE_SOURCES
    CH/Source/Activity/ActivityClassifier.cpp
    CH/Source/Activity/ActivityManager.cpp
    CH/Source/Activity/ActivityUtils.cpp
    CH/Source/Analytics/ActivitySummary.cpp
    CH/Source/Api/ActivityController.cpp
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
    CH/Source/WebView/WebViewController.cpp
    CH/Source/Window/Window.cpp)

# Keep vendored libraries as independent, narrow targets.  This avoids pulling
# their unrelated sources, examples, or build scripts into the application.
add_library(chronos_sqlite STATIC CH/ThirdParty/sqlite3.c)
target_include_directories(chronos_sqlite PUBLIC "${CHRONOS_THIRD_PARTY_DIR}")

add_library(chronos_argon2 STATIC
    CH/ThirdParty/argon2/src/argon2.c
    CH/ThirdParty/argon2/src/blake2/blake2b.c
    CH/ThirdParty/argon2/src/core.c
    CH/ThirdParty/argon2/src/encoding.c
    CH/ThirdParty/argon2/src/opt.c
    CH/ThirdParty/argon2/src/thread.c)
target_include_directories(chronos_argon2 PUBLIC
    "${CHRONOS_THIRD_PARTY_DIR}/argon2/include")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CHRONOS_WEBVIEW2_ARCH x64)
else()
    set(CHRONOS_WEBVIEW2_ARCH x86)
endif()

add_library(WebView2Loader SHARED IMPORTED GLOBAL)
set_target_properties(WebView2Loader PROPERTIES
    IMPORTED_IMPLIB "${CHRONOS_WEBVIEW2_DIR}/${CHRONOS_WEBVIEW2_ARCH}/WebView2Loader.dll.lib"
    IMPORTED_LOCATION "${CHRONOS_WEBVIEW2_DIR}/${CHRONOS_WEBVIEW2_ARCH}/WebView2Loader.dll")

add_library(chronos_core STATIC ${CHRONOS_CORE_SOURCES})
target_compile_features(chronos_core PUBLIC cxx_std_20)

target_compile_definitions(chronos_core PUBLIC
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    UNICODE
    _UNICODE)

target_compile_options(chronos_core PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>)
target_include_directories(chronos_core PUBLIC
    "${CHRONOS_SOURCE_DIR}/Include"
    "${CHRONOS_THIRD_PARTY_DIR}"
    "${CHRONOS_THIRD_PARTY_DIR}/argon2/include"
    "${CHRONOS_WEBVIEW2_DIR}/include")

add_library(chronos_asio INTERFACE)

target_include_directories(chronos_asio INTERFACE
    "${CHRONOS_THIRD_PARTY_DIR}/asio/include")


add_library(chronos_crow INTERFACE)

target_include_directories(chronos_crow INTERFACE
    "${CHRONOS_THIRD_PARTY_DIR}/crow/include")

target_link_libraries(chronos_crow INTERFACE
    chronos_asio)


target_link_libraries(chronos_core PUBLIC
    chronos_crow
    chronos_sqlite
    chronos_argon2
    WebView2Loader
    bcrypt)

add_executable(Chronos App/Main.cpp)
target_link_libraries(Chronos PRIVATE chronos_core)
set_target_properties(Chronos PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin/$<CONFIG>"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# WebView2's loader remains in the NuGet package; copy it beside the executable
# after every build instead of vendoring or modifying the package.
add_custom_command(TARGET Chronos POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:WebView2Loader>"
        "$<TARGET_FILE_DIR:Chronos>"
    VERBATIM)

if(CHRONOS_BUILD_TESTS)
    # This vendored GoogleTest release predates current CMake policy support.
    # Compile its single aggregation unit, matching the former VS project,
    # instead of configuring the third-party project's own CMake files.
    add_library(chronos_gtest STATIC
        CH/ThirdParty/googletest/src/gtest-all.cc)
    target_compile_features(chronos_gtest PUBLIC cxx_std_17)
    target_include_directories(chronos_gtest PUBLIC
        "${CHRONOS_THIRD_PARTY_DIR}/googletest/include"
        "${CHRONOS_THIRD_PARTY_DIR}/googletest")

    add_executable(ChronosTests
        App/TestMain.cpp
        CH/Test/SQLiteActivityStorageTest.cpp
        CH/Test/SQLiteTagStorageTest.cpp
        CH/Test/SQLiteUserStorageTest.cpp
        CH/Test/UserManagerTest.cpp)
    target_link_libraries(ChronosTests PRIVATE chronos_core chronos_gtest)
    set_target_properties(ChronosTests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin/$<CONFIG>")
    add_test(NAME ChronosTests COMMAND ChronosTests)
endif()
