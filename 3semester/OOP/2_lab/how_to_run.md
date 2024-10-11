Required packages
cmake, ninja(recommended), clang/gcc, clang-format

Before run
```sh
mv 1.cpp main.cpp
```

Run
```sh
mkdir build
cd build
cmake .. -G=Ninja
ninja -j$(nproc)
./2_lab
```