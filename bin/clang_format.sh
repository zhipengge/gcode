#!/bin/bash
# Applies clang-format

# perform clang-format on all cpp-files
file_list=$(find . -type f ! -path "./build*" ! -path "./src/cv/font_buffer.h" ! -path "./cmake*" ! -path ".git/*" ! -path "./dependencies/*" ! -name "*pb.cc" ! -path "*generated" | grep -E ".*(\c|\.cc|\.cpp|\.h|\.h)$")
clang-format --style=file $file_list -i --verbose
echo "clang-format done."