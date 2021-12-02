cmake_minimum_required(VERSION 3.7)
project(SubHook)

file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/Source/*.c)

add_library(subhook STATIC ${SOURCES})

target_include_directories(subhook
    PUBLIC ${PROJECT_SOURCE_DIR}/Include/
    PRIVATE ${PROJECT_SOURCE_DIR}/Include/SubHook/)