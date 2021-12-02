cmake_minimum_required(VERSION 3.7)
project(JSON)

add_library(json STATIC
    ${PROJECT_SOURCE_DIR}/Source/JSON.cpp)

target_include_directories(json
    PUBLIC ${PROJECT_SOURCE_DIR}/Include/
    PRIVATE ${PROJECT_SOURCE_DIR}/Include/JSON/)