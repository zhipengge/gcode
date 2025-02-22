#!/bin/bash
bash build.sh -a x86 -m Release -j 30
# bash build.sh -a x86 -m Debug -j 30
# bash build.sh -a aarch64 -m Release -j 30
# bash build.sh -a aarch64 -m Debug -j 30
# # unit test
# for test in $(find tests -name "*_test"); do
#     echo "================================="
#     echo "Running $test"
#     $test
# done
# ./main