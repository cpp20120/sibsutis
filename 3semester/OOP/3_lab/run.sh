#!/bin/bash

mkdir -p build

cp input.txt build/

cd build

cmake .. -G=Ninja

ninja -j$(nproc)

./lab3
