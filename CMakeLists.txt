cmake_minimum_required(VERSION 3.5)
project(puzzledpictures VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure Qt
set(QT_STATIC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)


set (OpenCV_DIR /usr/local/Cellar/opencv/4.9.0_12/lib/cmake/opencv4) # update this based on location of opencv install
find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "OpenCV not found. Install using apt-get or brew.")
endif()

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

qt_add_executable(puzzledpictures
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    README.md
)


target_link_libraries(puzzledpictures PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${OpenCV_LIBS}
)

qt_finalize_executable(puzzledpictures)
