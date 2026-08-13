cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE
    "C:/Users/24156/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project(Chronos LANGUAGES C CXX)
include(CTest)

# The application is Windows-only (Win32 APIs and WebView2).
if(NOT WIN32)
    message(FATAL_ERROR "Chronos currently supports Windows only.")
endif()

add_subdirectory(Chronos)
