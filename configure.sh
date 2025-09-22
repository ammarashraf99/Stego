#!/bin/bash

mkdir build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug
cp ./build/compile_commands.json .
