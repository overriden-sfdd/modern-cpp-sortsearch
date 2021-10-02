cmake_minimum_required(VERSION 3.14)

set(SORT_SOURCES src/sort_engine.cpp include/sort_engine.hpp)
set(SEARCH_SOURCES src/search_engine.cpp include/search_engine.hpp)

add_library(${PROJECT_NAME} ${SORT_SOURCES} ${SEARCH_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    INTERFACE
        "$<INSTALL_INTERFACE:include>"
)