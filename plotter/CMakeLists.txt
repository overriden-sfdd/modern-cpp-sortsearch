cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)

# Find Python
find_package(PythonLibs REQUIRED)
find_package(Python REQUIRED COMPONENTS Interpreter Development)

# Find matplotlib
find_package(matplotlib_cpp REQUIRED)

add_executable(DrawMePlot main.cpp)
target_link_libraries(DrawMePlot PRIVATE ${PROJECT_NAME})
target_link_libraries(DrawMePlot PRIVATE ${PYTHON_LIBRARIES})

target_include_directories(DrawMePlot PRIVATE ${PYTHON_INCLUDE_PATH})
target_include_directories(DrawMePlot PRIVATE ${matplotlib_cpp_DIRS})
target_link_libraries(DrawMePlot PRIVATE ${matplotlib_cpp_LIBS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)