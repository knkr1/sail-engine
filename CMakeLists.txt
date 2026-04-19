cmake_minimum_required(VERSION 4.2.3)
project(sail-engine VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.c)

add_executable(program ${SOURCES})

add_custom_command(TARGET program POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory "$<TARGET_FILE_DIR:program>/shaders"
    COMMAND ${CMAKE_COMMAND} -E remove_directory "$<TARGET_FILE_DIR:program>/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/src/shaders" "$<TARGET_FILE_DIR:program>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/src/assets" "$<TARGET_FILE_DIR:program>/assets"
)

target_include_directories(program PRIVATE 
src/
include/
)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(program PRIVATE glfw glm::glm opengl32)

target_sources(program PRIVATE src/glad.c)