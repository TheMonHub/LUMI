#
# LUMI - A game engine that is not a game engine
# =========================================
# Generate a command-line tool for managing LUMI projects.
#
# Build options:
# Name - Description

cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
project(LUMI
        VERSION 0.1.0
        DESCRIPTION "A game engine that is not a game engine"
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(GETOPT_SOURCES
        _deps/getopt/getopt.c
        _deps/getopt/getopt.h
)

add_library(getopt STATIC ${GETOPT_SOURCES})

set(LUMI_SOURCES
        src/main.c
        src/error.c
        src/error.h
        src/commands/help.c
        src/commands/help.h
        src/commands/version.c
        src/commands/version.h
        src/commands/new.c
        src/commands/new.h
        src/osal/windows.c
        src/osal/osal.h
)

set(LUMI_UNIX_SOURCES
        src/osal/unix.c
)

set(LUMI_WINDOWS_SOURCES
        src/osal/windows.c
)

if(WIN32)
    list(APPEND LUMI_SOURCES ${LUMI_WINDOWS_SOURCES})
else()
    list(APPEND LUMI_SOURCES ${LUMI_UNIX_SOURCES})
endif()

add_executable(lumi ${LUMI_SOURCES})

target_compile_definitions(
        lumi
        PRIVATE
        PROJECT_VERSION="${PROJECT_VERSION}"
)

target_include_directories(
        lumi
        PRIVATE
        src
        _deps
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LUAJIT REQUIRED IMPORTED_TARGET luajit)

set(LUAJIT_EXPECTED_VERSION 2.1)

if(LUAJIT_VERSION)
    if(LUAJIT_VERSION VERSION_LESS LUAJIT_EXPECTED_VERSION)
        message(FATAL_ERROR "LuaJIT too new: ${LUAJIT_VERSION}\n Expected: ${LUAJIT_EXPECTED_VERSION}")
    endif()
endif()

target_link_libraries(lumi PRIVATE PkgConfig::LUAJIT getopt)