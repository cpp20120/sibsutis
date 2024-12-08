#!/bin/bash

mkdir -p build
cd build
cmake .. -G=Ninja
ninja -j$(nproc)
./13_lab
