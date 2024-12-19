#!/bin/bash
# 默认值
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color
architecture="x86"
build_mode="Release"
output_dir="build"
jobs=6
function main() {
    # 处理命令行选项
    while [[ $# -gt 0 ]]; do
    case "$1" in
        -a|--architecture)
        shift
        architecture="$1"
        ;;
        -m|--mode)
        shift
        build_mode="$1"
        ;;
        -o|--output)
        shift
        output_dir="$1"
        ;;
        -j|--jobs)
        shift
        jobs="$1"
        ;;
        *)
        echo "用法: $0 [-a <编译架构>] [-m <编译模式>] [-o <输出目录>]"
        exit 1
        ;;
    esac
    shift
    done

    # 检查编译架构是否合法
    if [[ "$architecture" != "x86" && "$architecture" != "aarch64" ]]; then
    echo "不支持的编译架构: $architecture"
    exit 1
    fi

    # 检查编译模式是否合法
    if [[ "$build_mode" != "Release" && "$build_mode" != "Debug" ]]; then
    echo "不支持的编译模式: $build_mode"
    exit 1
    fi

    # 创建输出目录（如果不存在）
    mkdir -p "$output_dir"

    # 设置构建目录，命名方式为 架构_模式
    build_dir="$output_dir/$architecture"_"$build_mode"

    # 创建构建目录（如果不存在）
    if [ -d $build_dir ];then
        echo "remove "$build_dir
        rm -rf $build_dir
    fi
    mkdir -p "$build_dir"
    # compile config
    echo -e "${GREEN}======================================="
    echo -e "${GREEN}编译架构: $architecture"
    echo -e "${GREEN}编译模式: $build_mode"
    echo -e "${GREEN}输出目录: $build_dir"
    echo -e "${GREEN}并行任务: $jobs"
    echo -e "${GREEN}=======================================${NC}"
    # sleep 1s
    sleep 1
    # 使用CMake进行编译
    echo "开始编译..."
    cmake -S . -B "$build_dir" -DARCHITECTURE="$architecture" -DCMAKE_BUILD_TYPE="$build_mode"
    cmake --build "$build_dir"  -j $jobs
    echo "编译完成。"
    cd $build_dir
    pwd
    # unit test
    for test in $(find tests -name "*_test"); do
        echo "================================="
        echo "Running $test"
        $test
    done
./main
}

main "$@"