cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)

add_executable(TaskG5 main.cpp)
target_link_libraries (TaskG5 ${PROJECT_NAME})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)
