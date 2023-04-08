cmake_minimum_required(VERSION 3.10)
project(gcode)
set(CMAKE_CXX_STANDARD 17)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)


################# submodlue #################
# gtest
add_subdirectory(dependencies/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_FILES)

add_definitions(-DGLOG)


#################### lib ####################
add_library(gcode ${SRC_FILES})
set_target_properties(gcode PROPERTIES OUTPUT_NAME "gcode")


#################### main ####################
add_executable(main main.cc)
target_link_libraries(main gcode)


#################### test ####################
file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cc)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/tests)
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} gtest gtest_main gcode)
    set_target_properties(${TEST_NAME} PROPERTIES OUTPUT_NAME ${CMAKE_SOURCE_DIR}/build/tests/${TEST_NAME})
    add_test(NAME ${TEST_NAME} COMMAND ${CMAKE_SOURCE_DIR}/build/tests/${TEST_NAME})
endforeach()