cmake_minimum_required(VERSION 3.7)
project(RakNet)

file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/Source/*.cpp)

add_library(raknet STATIC ${SOURCES})

target_include_directories(raknet
    PUBLIC ${PROJECT_SOURCE_DIR}/Include/
    PRIVATE ${PROJECT_SOURCE_DIR}/Include/RakNet/)

target_link_libraries(raknet PUBLIC ws2_32)