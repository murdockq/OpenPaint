cmake_minimum_required(VERSION 3.15)

project(OpenPaint
    VERSION 1.3.0
    DESCRIPTION "Cross-platform open source alternative to MS Paint"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

option(OPENPAINT_BUILD_APP   "Build the OpenPaint GUI application" ON)
option(OPENPAINT_BUILD_TESTS "Build the unit tests"               ON)
option(OPENPAINT_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

if(OPENPAINT_BUILD_APP)
    add_subdirectory(OpenPaint)
endif()

if(OPENPAINT_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.3)
    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    add_subdirectory(tests)
endif()
