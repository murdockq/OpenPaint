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

function(openpaint_copy_runtime_dlls target_name)
    if(WIN32)
        set(openpaint_applocal_script "")
        if(DEFINED CMAKE_TOOLCHAIN_FILE)
            get_filename_component(openpaint_toolchain_dir "${CMAKE_TOOLCHAIN_FILE}" DIRECTORY)
            set(openpaint_applocal_script
                "${openpaint_toolchain_dir}/msbuild/applocal.ps1")
        endif()

        set(openpaint_installed_prefix "")
        if(DEFINED VCPKG_INSTALLED_DIR AND DEFINED VCPKG_TARGET_TRIPLET)
            set(openpaint_installed_prefix
                "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}")
        elseif(CMAKE_PREFIX_PATH)
            list(GET CMAKE_PREFIX_PATH 0 openpaint_installed_prefix)
        endif()

        # Catch2 discovers tests by launching the executable during the build.
        # When dependencies come from vcpkg, use its recursive applocal helper
        # so wxWidgets' transitive DLLs are copied as well.
        if(EXISTS "${openpaint_applocal_script}" AND openpaint_installed_prefix)
            add_custom_command(TARGET ${target_name} POST_BUILD
                COMMAND powershell.exe -ExecutionPolicy Bypass -NoProfile -File
                    "${openpaint_applocal_script}"
                    "$<TARGET_FILE:${target_name}>"
                    "${openpaint_installed_prefix}/$<IF:$<CONFIG:Debug>,debug/bin,bin>"
                    "" ""
                COMMENT "Copying runtime DLLs next to ${target_name}"
            )
        else()
            add_custom_command(TARGET ${target_name} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy -t "$<TARGET_FILE_DIR:${target_name}>"
                    $<TARGET_RUNTIME_DLLS:${target_name}>
                COMMAND_EXPAND_LISTS
                COMMENT "Copying runtime DLLs next to ${target_name}"
            )
        endif()
    endif()
endfunction()

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
