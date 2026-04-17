cmake_minimum_required(VERSION 4.2)
project(LUMI
        VERSION 0.1.0
        DESCRIPTION "A game engine that is not a game engine"
)

set(CMAKE_C_STANDARD 17)

set(LUMI_SOURCES
        main.c
)

add_executable(lumi ${LUMI_SOURCES})