project(pycontainer)
cmake_minimum_required(VERSION 3.15)

add_executable(pycontainer main.cpp src/task.cpp)
target_include_directories(pycontainer PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_property(TARGET pycontainer PROPERTY CXX_STANDARD 11)