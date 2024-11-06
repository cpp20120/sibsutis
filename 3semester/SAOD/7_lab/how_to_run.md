# Required packages

cmake, ninja(recommended), clang/gcc, clang-format

# Run

```sh
mkdir build
cd build
cmake .. -G=Ninja
ninja -j$(nproc)
./7_lab
```

or just

```sh
chmod +x run.sh
./run.sh
```

# Clang-format

```sh
clang-format -i *.cpp *.hpp
```