cmake_minimum_required(VERSION 3.5)
project(puzzledpictures VERSION 0.1 LANGUAGES CXX)
enable_testing()


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

find_package(GTest)

find_package(OpenCV 4.9 REQUIRED)
message(${OpenCV_INCLUDE_DIRS})
message(STATUS "OpenCV_VERSION: ${OpenCV_VERSION}")

if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "OpenCV not found. Install using apt-get or brew.")
endif()


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
    ${OpenCV_LIBS}
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main)

qt_finalize_executable(puzzledpictures)


get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()
