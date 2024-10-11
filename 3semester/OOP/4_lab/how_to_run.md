Required packages cmake, ninja(recommended), clang/gcc, clang-format

Run

```sh
mkdir build
cp input.txt ./build
cd build
cmake .. -G=Ninja
ninja -j$(nproc)
./lab4
```

or just

```sh
chmod +x run.sh
./run.sh
```
