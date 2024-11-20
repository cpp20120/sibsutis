mkdir build
cd build
cmake .. -G=Ninja
ninja -j$(nproc)
./3_task