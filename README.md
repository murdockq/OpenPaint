OpenPaint
=========
[![CI](https://github.com/murdockq/OpenPaint/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/murdockq/OpenPaint/actions/workflows/ci.yml)

The cross-platform open source alternative to MS Paint. 

## About ##
Open Paint is an open source image editor for all major operating systems. The goal of this application is to create a simple to use image editor that has all the functionality an average computer user would need.  This leaves GIMP and Paint.NET for professional users and allows the project to focus on ease of use and intuitive interface over feature completeness.

## Features ##

 * Familiar layout
 * Multiple tabs for each image
 * Support for most major image types (BMP, PNG, JPEG, GIF, PCX, PNM, TIF, XPM, ICO, CUR)
 * Tools like pencil, paintbrush, fill, text, eye dropper, eraser, magnify, selection (rectangular + lasso), shapes (rectangle, rounded rectangle, ellipse, polyline) and more...
 * Image options for resize, scale, rotating (90° and arbitrary angle), flipping and more...
 * Filters for invert, blur, pixelize, grayscale, monotone and more...

## Requirements ##

* **Windows:** install wxWidgets via [vcpkg](https://vcpkg.io/) (`vcpkg install wxwidgets`).
* **Linux:** `sudo apt-get install libwxgtk3.2-dev`
* **macOS:** `brew install wxwidgets`

## Building ##

OpenPaint uses [CMake](https://cmake.org/) and [wxWidgets](https://www.wxwidgets.org/).

```sh
# Configure (from the repo root)
cmake -B build

# Build the application
cmake --build build --config Release

# Build and run the unit tests
cmake -B build -DOPENPAINT_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

Build options:
* `-DOPENPAINT_BUILD_APP=ON/OFF`   - build the GUI application (default: ON)
* `-DOPENPAINT_BUILD_TESTS=ON/OFF` - build the unit tests (default: ON)
* `-DOPENPAINT_WARNINGS_AS_ERRORS=ON` - treat compiler warnings as errors

Platform wxWidgets install:
* **Linux:** `sudo apt-get install libwxgtk3.2-dev`
* **macOS:** `brew install wxwidgets`
* **Windows:** install via [vcpkg](https://vcpkg.io/) (`vcpkg install wxwidgets`) and pass
  `-DCMAKE_TOOLCHAIN_FILE=<vcpkg>/scripts/buildsystems/vcpkg.cmake` to CMake.
