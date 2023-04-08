# arm_toolchain.cmake

# 设置CMake的编译器为ARM交叉编译工具链
set(CMAKE_SYSTEM_NAME Linux) # 适用的操作系统名称
set(CMAKE_C_COMPILER /usr/bin/gcc) # 指定ARM交叉编译器的路径
set(CMAKE_CXX_COMPILER /usr/bin/g++) # 指定ARM交叉编译器的路径

# 设置ARM编译架构
set(CMAKE_SYSTEM_PROCESSOR arm)

# 指定编译工具链中的库和头文件路径，如果需要的话
# set(CMAKE_FIND_ROOT_PATH ${CMAKE_SOURCE_DIR}/arm-toolchain.cmake)

# 其他与交叉编译相关的设置
