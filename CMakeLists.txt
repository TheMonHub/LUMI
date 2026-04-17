cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
project(LUMI
        VERSION 0.1.0
        DESCRIPTION "A game engine that is not a game engine"
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(LUMI_SOURCES
        src/main.c
)

add_executable(lumi ${LUMI_SOURCES})

target_include_directories(
        lumi
        PRIVATE
        src
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LUAJIT REQUIRED IMPORTED_TARGET luajit)

set(LUAJIT_EXPECTED_VERSION 2.1)

if(LUAJIT_VERSION)
    if(LUAJIT_VERSION VERSION_LESS LUAJIT_EXPECTED_VERSION)
        message(FATAL_ERROR "LuaJIT too new: ${LUAJIT_VERSION}\n Expected: ${LUAJIT_EXPECTED_VERSION}")
    endif()
endif()

target_link_libraries(lumi PRIVATE PkgConfig::LUAJIT)