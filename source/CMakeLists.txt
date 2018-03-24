cmake_minimum_required(VERSION 3.7)
project(source)

SET(SDL2_SEARCH_PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        ${SDL2_PATH}
        )

FIND_PATH(SDL2_INCLUDE_DIR SDL.h
        HINTS
        $ENV{SDL2DIR}
        PATH_SUFFIXES include/SDL2 include
        PATHS ${SDL2_SEARCH_PATHS}
        )

FIND_LIBRARY(SDL2_LIBRARY_TEMP
        NAMES SDL2
        HINTS
        $ENV{SDL2DIR}
        PATH_SUFFIXES lib64 lib
        PATHS ${SDL2_SEARCH_PATHS}
        )

FIND_LIBRARY(SDL2MAIN_LIBRARY
        NAMES SDL2main
        HINTS
        $ENV{SDL2DIR}
        PATH_SUFFIXES lib64 lib
        PATHS ${SDL2_SEARCH_PATHS}
        )

FIND_PACKAGE(Threads)

SET(MINGW32_LIBRARY mingw32 CACHE STRING "mwindows for MinGW")
SET(SDL2_LIBRARY_TEMP ${MINGW32_LIBRARY} ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2 REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp ProjetFinal.h Menu.h MainMenu.h Settings.h InGameOverlay.h InGameESC.h Image2D.h RotatingImage.h TextureID.h Resource.h ResourceManager.h ResourceManager.h)
add_executable(source ${SOURCE_FILES})
target_link_libraries(source ${SDL2_LIBRARY_TEMP})
