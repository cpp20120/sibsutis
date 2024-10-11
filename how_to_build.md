Required packages
cmake, ninja/msbuild , msvc/clang/gcc, clang-format

Before run
```sh
mv 1.cpp main.cpp
```
ninja:
Run
```sh
mkdir build
cd build
cmake .. -G=Ninja
ninja -j$(nproc)
./<name of project>
```

msbuild:
Run 
```sh
mkdir build 
cd build
cmake -G "Visual Studio 17 2022" -B build
open VS project file and build
```


* on windows comment using mold linker usage(and on linux) if you won't install it:
  ```cmake
  (set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=mold"))
  ```