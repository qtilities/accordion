cmake_minimum_required(VERSION 3.5)
project(Accordion
    VERSION 0.1
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#===============================================================================
# Qt
#===============================================================================
option(PROJECT_TRANSLATIONS_UPDATE "Update source translations [default: OFF]" OFF)
set(PROJECT_QT_VERSION 5 CACHE STRING "Qt version to use [default: 5]")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(QT NAMES Qt${PROJECT_QT_VERSION})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED Widgets)
#===============================================================================
# Project files
#===============================================================================
set(PROJECT_ALL_FILES
    src/accordion.hpp
    src/accordion.cpp
    example/mainwindow.hpp
    example/mainwindow.cpp
    example/main.cpp
)
set(PROJECT_OTHER_FILES
#   .github/workflows/build.yml
    .clang-format
    .editorconfig
    .gitattributes
    .gitignore
    README.md
)
source_group("Other Files" FILES ${PROJECT_OTHER_FILES})
#===============================================================================
# Application executable
#===============================================================================
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_ALL_FILES})
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED ${PROJECT_ALL_FILES})
    else()
        add_executable(${PROJECT_NAME} ${PROJECT_ALL_FILES})
    endif()
endif()

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Widgets
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
