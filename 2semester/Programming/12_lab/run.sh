mkdir build
cd build
cmake .. -G=Ninja
ninja -j$(nproc)
./12_lab