cmake_minimum_required(VERSION 3.10)
project(gcode)
set(CMAKE_CXX_STANDARD 17)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/base
  ${CMAKE_CURRENT_SOURCE_DIR}/src/common
  ${CMAKE_CURRENT_SOURCE_DIR}/src/cv
  ${CMAKE_CURRENT_SOURCE_DIR}/src/nn
  ${CMAKE_CURRENT_SOURCE_DIR}/src/leetcode
)


################# submodlue #################
# gtest
add_subdirectory(dependencies/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# stb
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb)
# eigen
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/eigen)

# recursive source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)


add_definitions(-DGLOG -DSTB_IMAGE_IMPLEMENTATION -DSTB_IMAGE_WRITE_IMPLEMENTATION)

#################### lib ####################

# 根据构建类型设置库的类型
add_library(gcode SHARED ${SRC_FILES})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # 添加debug信息
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set_target_properties(gcode PROPERTIES DEBUG_POSTFIX "_d")
    message("编译Debug版本的库...")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(gcode PROPERTIES DEBUG_POSTFIX "")
    message("编译Release版本的库...")
else()
    message(FATAL_ERROR "不支持的构建类型: ${CMAKE_BUILD_TYPE}")
endif()
set_target_properties(gcode PROPERTIES OUTPUT_NAME "gcode")


#################### main ####################
add_executable(main main.cc)

################# compiling #################
if (ARCHITECTURE STREQUAL "x86")
    message("配置为x86编译架构...")
    set(CMAKE_SYSTEM_PROCESSOR "x86")
    target_compile_definitions(main PRIVATE __x86__)
    message("启用64位编译...")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    message("启用SSE3支持...")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3")

    # 添加其他特定于x86编译架构的编译选项
    set(CMAKE_TOOLCHAIN_FILE x86-toolchain.cmake)

  elseif (ARCHITECTURE STREQUAL "aarch64")
      message("配置为aarch64编译架构...")
      target_compile_definitions(main PRIVATE __aarch64__)
      # 添加其他特定于x86编译架构的编译选项
      set(CMAKE_TOOLCHAIN_FILE arm-toolchain.cmake)

else ()
    message(FATAL_ERROR "不支持的编译架构: ${ARCHITECTURE}")
endif()
target_link_libraries(main gcode)


#################### test ####################
file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cc)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${ARCHITECTURE}_${CMAKE_BUILD_TYPE}/tests)
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} gtest gtest_main gcode)
    set_target_properties(${TEST_NAME} PROPERTIES OUTPUT_NAME ${CMAKE_SOURCE_DIR}/build/${ARCHITECTURE}_${CMAKE_BUILD_TYPE}/tests/${TEST_NAME})
    add_test(NAME ${TEST_NAME} COMMAND ${CMAKE_SOURCE_DIR}/build/${ARCHITECTURE}_${CMAKE_BUILD_TYPE}/tests/${TEST_NAME})
endforeach()