# Development environment for labs:

```sh
chmod +x setup.sh
./setup.sh fedora   # для Fedora
./setup.sh debian   # для Debian, Ubuntu
./setup.sh arch     # для Arch
./setup.sh macos    # для macOS
```

```sh
./setup.ps1 # для windows
```

Вам нужно будет выбрать нужные компоненты для Visual Studio(указаны ниже)

## C
- Linux
```sh
gcc/clang
```

- Windows
```sh
clang-cl/msys(prefer clang please)
```

- MacOS
```sh
clang 
```

## Cpp

- Linux:
```sh
cmake
ninja
make(for trpo)
GTest
clang/gcc
clang-format
```
- Windows:
### Without VS
```sh
cmake
ninja
clang(clang-cl(please don't use mingw's trash))
clang-format
```
### With VS
install components for visual studio
```sh
Linux and embedded development(if it is trpo)
development of classic apps on C++
```

- MacOS:
```sh
cmake
ninja
GTest
make(for trpo)
clang/gcc
clang-format
```

Libraries:
```sh
sfml
qt6
```

## CSharp

- Linux, Windows and MacOS:
### Without VS
```sh
vscode
dotnet(dotnet runtime and sdk)
C# dev kit
```

- Windows:
### With VS
install components for visual studio
```sh
Development of classic apps .NET
```

### SQL on informatics
```
sqlite
sqlite studio
```