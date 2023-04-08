cmake_minimum_required(VERSION 3.10)
project(gcode)
set(CMAKE_CXX_STANDARD 17)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_FILES)

add_definitions(-DGLOG)

add_executable(gcode main.cc ${SRC_FILES})