#!/bin/bash
# rm -rf build/
# mkdir build/
# cd build/
# cmake ..
# make -j4
# bash build.sh -a x86 -m Release
# bash build.sh -a x86 -m Debug
bash build.sh -a aarch64 -m Release
# # unit test
# for test in $(find tests -name "*_test"); do
#     echo "================================="
#     echo "Running $test"
#     $test
# done
# ./main