#!/bin/bash

mkdir -p build

cp recipes.txt build/

cd build

cmake .. -G=Ninja

ninja -j$(nproc)

./lab4
