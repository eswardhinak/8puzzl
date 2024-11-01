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
    message(STATUS "OpenCV not found, using FetchContent to download it.")
        FetchContent_Declare(
          opencv
          GIT_REPOSITORY https://github.com/opencv/opencv.git
          GIT_TAG 4.x  # You can set a specific tag like 4.9.0
        )
        FetchContent_MakeAvailable(opencv)
        set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui) # Add required OpenCV libraries
endif()
message(STATUS "OpenCV version: ${OpenCV_VERSION}")


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
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET puzzledpictures APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(puzzledpictures SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(puzzledpictures
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(puzzledpictures PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${OpenCV_LIBS}
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main)

# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.puzzledpictures)
endif()
set_target_properties(puzzledpictures PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    # MACOSX_BUNDLE TRUE
    # WIN32_EXECUTABLE TRUE
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


get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()


