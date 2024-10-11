Required packages cmake, ninja(recommended), clang/gcc, clang-format

Run

```sh
mkdir build
cp input.txt ./build
cd build
cmake .. -G=Ninja
ninja -j$(nproc)
./3_lab
```

or just

```sh
chmod +x run.sh
./run.sh
```
