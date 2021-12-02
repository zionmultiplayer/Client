cmake_minimum_required(VERSION 3.7)
project(Game)

file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/Source/*.cpp)

add_library(game STATIC ${SOURCES})

target_include_directories(game
    PUBLIC ${PROJECT_SOURCE_DIR}/Include/
    PRIVATE ${PROJECT_SOURCE_DIR}/Include/Game/)