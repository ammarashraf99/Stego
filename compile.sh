#!/bin/bash

proj_root_path="/home/ammar/programming/data-hiding"

cd ${proj_root_path}/build
cmake --build .

cp ./src/stegtool/stegtool .
