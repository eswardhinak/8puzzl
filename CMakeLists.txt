set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
cmake_minimum_required(VERSION 3.5)
project(puzzledpictures VERSION 0.1 LANGUAGES CXX)

# Enable static linking globally
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)

enable_testing()
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent for dependency management
include(FetchContent)

# Configure and fetch GTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
find_package(GTest)

# Configure Qt
set(QT_STATIC ON)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "OpenCV not found. Install using apt-get or brew.")
endif()

# Set the location of the libraries after they're built
set_target_properties(opencv_core PROPERTIES
    IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/opencv_install/lib/libopencv_core.a
)
set_target_properties(opencv_imgproc PROPERTIES
    IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/opencv_install/lib/libopencv_imgproc.a
)
set_target_properties(opencv_imgcodecs PROPERTIES
    IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/opencv_install/lib/libopencv_imgcodecs.a
)
set_target_properties(opencv_highgui PROPERTIES
    IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/opencv_install/lib/libopencv_highgui.a
)

# Project sources
set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/tst_maintest.cpp
        src/multiimageclass.h src/multiimageclass.cpp
        src/gametilepixmapitem.h src/gametilepixmapitem.cpp
        src/boardstate.h src/boardstate.cpp
    )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(puzzledpictures
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        README.md
    )
else()
    message(FATAL_ERROR, "Qt version >= 6 required")
endif()


target_link_libraries(puzzledpictures PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    opencv_core
    opencv_imgproc
    opencv_imgcodecs
    opencv_highgui
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

qt_finalize_executable(puzzledpictures)


get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()
