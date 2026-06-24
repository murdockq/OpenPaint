# Unit tests for the non-GUI core of OpenPaint.
#
# History, ImageOps, ConfigFile and the bundled tinyxml have no dependency on
# wxWidgets, so the test executable links only against those translation
# units plus Catch2. The ToolManager test exercises the colour/brush
# settings that don't require a running application.

set(OPENPAINT_CORE_SOURCES
    ${CMAKE_SOURCE_DIR}/OpenPaint/ConfigFile.cpp
    ${CMAKE_SOURCE_DIR}/OpenPaint/History.h
    ${CMAKE_SOURCE_DIR}/OpenPaint/ImageOps.cpp
    ${CMAKE_SOURCE_DIR}/OpenPaint/tinyxml.cpp
    ${CMAKE_SOURCE_DIR}/OpenPaint/tinyxmlerror.cpp
    ${CMAKE_SOURCE_DIR}/OpenPaint/tinyxmlparser.cpp
    ${CMAKE_SOURCE_DIR}/OpenPaint/tinystr.cpp
)

add_library(openpaint_core STATIC ${OPENPAINT_CORE_SOURCES})
target_include_directories(openpaint_core PUBLIC ${CMAKE_SOURCE_DIR}/OpenPaint)
target_compile_definitions(openpaint_core PUBLIC TIXML_USE_STL)

add_executable(test_openpaint
    test_ConfigFile.cpp
    test_History.cpp
    test_ImageOps.cpp
)
target_link_libraries(test_openpaint PRIVATE openpaint_core Catch2WithMain)

target_compile_definitions(test_openpaint PRIVATE TIXML_USE_STL)

if(MSVC)
    target_compile_options(test_openpaint PRIVATE /W4 /permissive-)
else()
    target_compile_options(test_openpaint PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(OPENPAINT_WARNINGS_AS_ERRORS)
    if(MSVC)
        target_compile_options(test_openpaint PRIVATE /WX)
    else()
        target_compile_options(test_openpaint PRIVATE -Werror)
    endif()
endif()

include(Catch)
catch_discover_tests(test_openpaint)

# WebP round-trip test. Linked against wx::core so the test exercises the
# same libwebp the GUI uses. Skipped automatically if wxWidgets isn't
# available (e.g. developer installed only the libraries needed for the
# non-GUI tests).
find_package(wxWidgets CONFIG QUIET COMPONENTS core base)
if(NOT wxWidgets_FOUND)
    find_package(wxWidgets QUIET MODULE COMPONENTS core base)
endif()
if(wxWidgets_FOUND)
    if(TARGET wx::core)
        add_executable(test_openpaint_webp test_Webp.cpp)
        target_link_libraries(test_openpaint_webp PRIVATE
            openpaint_core Catch2WithMain wx::core wx::base)
    else()
        add_executable(test_openpaint_webp test_Webp.cpp)
        target_include_directories(test_openpaint_webp PRIVATE ${wxWidgets_INCLUDE_DIRS})
        target_compile_options(test_openpaint_webp PRIVATE ${wxWidgets_CXX_FLAGS})
        target_link_libraries(test_openpaint_webp PRIVATE
            openpaint_core Catch2WithMain ${wxWidgets_LIBRARIES})
    endif()
    if(MSVC)
        target_compile_options(test_openpaint_webp PRIVATE /W4 /permissive-)
    else()
        target_compile_options(test_openpaint_webp PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    catch_discover_tests(test_openpaint_webp)
endif()
