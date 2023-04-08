#!/bin/bash

rm -rf build/
mkdir build/
cd build/
cmake ..
make -j4
# unit test
for test in $(find tests -name "*_test"); do
    echo "================================="
    echo "Running $test"
    $test
done
./main