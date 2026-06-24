# OpenPaint GUI application target
#
# Links against wxWidgets (aui, xml, adv, html, core, base). On Linux/macOS the
# wxWidgets package is typically found automatically via wx-config. On Windows
# build wxWidgets with MSVC and point CMAKE_PREFIX_PATH at it, or use vcpkg.

# Prefer the CMake config-package (vcpkg, MSVC builds). Fall back to the
# wx-config based module on Linux/macOS.
find_package(wxWidgets CONFIG QUIET COMPONENTS aui xml adv html core base)
if(wxWidgets_FOUND)
    set(OPENPAINT_WX_TARGETS wx::aui wx::xml wx::adv wx::html wx::core wx::base)
else()
    find_package(wxWidgets REQUIRED MODULE COMPONENTS aui xml adv html core base)
    set(OPENPAINT_WX_TARGETS ${wxWidgets_LIBRARIES})
    target_include_directories(openpaint PRIVATE ${wxWidgets_INCLUDE_DIRS})
    target_compile_options(openpaint PRIVATE ${wxWidgets_CXX_FLAGS})
endif()

set(OPENPAINT_SOURCES
    ConfigFile.cpp
    Globals.cpp
    IconLoader.cpp
    ImageOps.cpp
    OpenPaintGUI.cpp
    OpenPaintMainApp.cpp
    OpenPaintMDIChildFrame.cpp
    SubBrushToolPanel.cpp
    SubEraserToolPanel.cpp
    SubPencilToolPanel.cpp
    SubShapeToolPanel.cpp
    SubSprayCanToolPanel.cpp
    SubTextToolPanel.cpp
    SubMainFrame.cpp
    SubToolPanel.cpp
    SubCanvasSizeDialog.cpp
    SubImageSizeDialog.cpp
    SubColorPanel.cpp
    PaletteCtrl.cpp
    ToolManager.cpp
    tinystr.cpp
    tinyxml.cpp
    tinyxmlerror.cpp
    tinyxmlparser.cpp
)

set(OPENPAINT_HEADERS
    ConfigFile.h
    Globals.h
    IconLoader.h
    ImageOps.h
    OpenPaintGUI.h
    OpenPaintMainApp.h
    OpenPaintMDIChildFrame.h
    SubBrushToolPanel.h
    SubEraserToolPanel.h
    SubPencilToolPanel.h
    SubShapeToolPanel.h
    SubSprayCanToolPanel.h
    SubTextToolPanel.h
    SubMainFrame.h
    SubToolPanel.h
    SubCanvasSizeDialog.h
    SubImageSizeDialog.h
    SubColorPanel.h
    PaletteCtrl.h
    ToolManager.h
    tinystr.h
    tinyxml.h
    resource.h
    IconPaths.h.in
)

# Pin the on-disk locations of the SVG and XPM icon directories into a
# generated header. IconLoader.cpp #includes it to locate res/svg and res/
# regardless of the working directory the binary is launched from.
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/IconPaths.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/IconPaths.h"
    @ONLY
)
list(APPEND OPENPAINT_HEADERS
    "${CMAKE_CURRENT_BINARY_DIR}/generated/IconPaths.h"
)

add_executable(openpaint WIN32
    ${OPENPAINT_SOURCES}
    ${OPENPAINT_HEADERS}
    OpenPaint.rc
)

target_include_directories(openpaint PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)
target_compile_definitions(openpaint PRIVATE TIXML_USE_STL)

# Copy the SVG icons next to the binary so the loader can find them at
# runtime without requiring the source tree to be present. On multi-config
# generators the binary lives under <build>/<config>/, so we resolve the
# directory from the target itself.
add_custom_command(TARGET openpaint POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:openpaint>/res/svg"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/res/svg"
        "$<TARGET_FILE_DIR:openpaint>/res/svg"
    COMMENT "Copying SVG icons next to openpaint binary"
)

target_link_libraries(openpaint PRIVATE ${OPENPAINT_WX_TARGETS})

if(MSVC)
    target_compile_options(openpaint PRIVATE /W4 /permissive-)
else()
    target_compile_options(openpaint PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(OPENPAINT_WARNINGS_AS_ERRORS)
    if(MSVC)
        target_compile_options(openpaint PRIVATE /WX)
    else()
        target_compile_options(openpaint PRIVATE -Werror)
    endif()
else()
    # Several non-fatal warnings are produced by code that we either cannot
    # change (the bundled tinyxml, wxWidgets 3.3 deprecations of wxPen/wxBrush
    # integer-style constructors) or that comes from the event-table macros
    # (the `event` parameter is required by the macro signature even when the
    # handler does not use it). Keep the build at /W3 so we still catch
    # genuine mistakes.
    if(MSVC)
        target_compile_options(openpaint PRIVATE /W3)
    endif()
endif()

install(TARGETS openpaint RUNTIME DESTINATION bin)
