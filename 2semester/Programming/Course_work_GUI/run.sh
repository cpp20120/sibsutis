mkdir build
cd build
cmake .. -G=Ninja
ninja -j$(nproc)
./cursach