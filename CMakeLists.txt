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
set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Configure Qt
set(QT_STATIC ON)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Download and extract a specific OpenCV version
include(ExternalProject)
ExternalProject_Add(opencv_external
    URL https://github.com/opencv/opencv/archive/refs/tags/4.9.0.zip
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/opencv_install
        -DBUILD_SHARED_LIBS=OFF
        -DWITH_VTK=OFF
        -DOPENCV_ENABLE_VTK=OFF
        -DWITH_FFMPEG=OFF
        -DWITH_GTK=OFF
        -DWITH_QT=OFF
        -DWITH_TIFF=ON  # Add this line
        -DBUILD_TIFF=ON # And this line
        -DOPENCV_ENABLE_NONFREE=OFF
        -DBUILD_opencv_apps=OFF
        -DBUILD_EXAMPLES=OFF
        -DBUILD_PERF_TESTS=OFF
        -DBUILD_TESTS=OFF
        -DBUILD_opencv_python2=OFF
        -DBUILD_opencv_python3=OFF
        -DBUILD_opencv_java=OFF
        -DBUILD_LIST=core,imgproc,imgcodecs,highgui
        -DCMAKE_BUILD_TYPE=Release
    BUILD_COMMAND ${CMAKE_COMMAND} --build . --config Release
    INSTALL_COMMAND ${CMAKE_COMMAND} --install . --config Release
)

# Create an imported target for OpenCV components
add_library(opencv_core STATIC IMPORTED)
add_library(opencv_imgproc STATIC IMPORTED)
add_library(opencv_imgcodecs STATIC IMPORTED)
add_library(opencv_highgui STATIC IMPORTED)

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
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(puzzledpictures
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/tst_maintest.cpp
        src/multiimageclass.h src/multiimageclass.cpp
        src/gametilepixmapitem.h src/gametilepixmapitem.cpp
        src/boardstate.h src/boardstate.cpp
        README.md
    )
else()
    if(ANDROID)
        add_library(puzzledpictures SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(puzzledpictures
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Make sure OpenCV is built before our main target
add_dependencies(puzzledpictures opencv_external)

# Add OpenCV include directories
target_include_directories(puzzledpictures PRIVATE
    ${CMAKE_BINARY_DIR}/opencv_install/include/opencv4
)

# Link libraries
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

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.puzzledpictures)
endif()

set_target_properties(puzzledpictures PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

include(GNUInstallDirs)
install(TARGETS puzzledpictures
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(puzzledpictures)
endif()
