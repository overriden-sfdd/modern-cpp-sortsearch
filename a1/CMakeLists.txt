cmake_minimum_required(VERSION 3.10)
project(LifeGame VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(LIFE_GAME_FILES
    include/life.hpp
    src/life.cpp)

add_library(${PROJECT_NAME} ${LIFE_GAME_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")

add_executable(Life src/main.cpp)
target_link_libraries(Life ${PROJECT_NAME})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)