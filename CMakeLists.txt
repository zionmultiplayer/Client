cmake_minimum_required(VERSION 3.7)
project(Zion)

file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/Source/*.cc)

add_library(zion SHARED ${SOURCES})

target_include_directories(zion
    PUBLIC ${PROJECT_SOURCE_DIR}/Include/)

add_subdirectory(${PROJECT_SOURCE_DIR}/Libraries/Game)
add_subdirectory(${PROJECT_SOURCE_DIR}/Libraries/ImGui)
add_subdirectory(${PROJECT_SOURCE_DIR}/Libraries/JSON)
add_subdirectory(${PROJECT_SOURCE_DIR}/Libraries/RakNet)
add_subdirectory(${PROJECT_SOURCE_DIR}/Libraries/SubHook)

target_link_libraries(zion PUBLIC game imgui json raknet subhook pthread)
set_target_properties(zion PROPERTIES PREFIX "" SUFFIX ".asi")
target_compile_options(zion PUBLIC -masm=intel)