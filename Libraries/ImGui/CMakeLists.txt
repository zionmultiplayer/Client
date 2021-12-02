cmake_minimum_required(VERSION 3.7)
project(ImGui)

file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/Source/*.cpp)

add_library(imgui STATIC ${SOURCES})

target_include_directories(imgui
    PUBLIC ${PROJECT_SOURCE_DIR}/Include/
    PRIVATE ${PROJECT_SOURCE_DIR}/Include/ImGui/)

target_link_libraries(imgui PUBLIC dwmapi gdi32)