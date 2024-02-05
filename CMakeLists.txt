cmake_minimum_required(VERSION 3.15)
project(pycontainer VERSION 0.0.1)

add_executable(simple_container main.cpp src/task.cpp)
target_include_directories(simple_container PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_property(TARGET simple_container PROPERTY CXX_STANDARD 11)

add_library(simple_container_taskmgr SHARED src/task.cpp)
target_include_directories(simple_container_taskmgr PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_property(TARGET simple_container_taskmgr PROPERTY CXX_STANDARD 11)

add_subdirectory(extern/pybind11)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
# target_link_libraries(<your exe or lib> ${PYTHON_LIBRARIES})

pybind11_add_module(pycontainer pybind/pycontainer.cpp)
target_include_directories(pycontainer PUBLIC ${CMAKE_SOURCE_DIR}/extern/pybind11/include ${PYTHON_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(pycontainer PUBLIC simple_container_taskmgr)