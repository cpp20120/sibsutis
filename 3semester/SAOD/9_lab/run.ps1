mkdir build
cd build

cmake .. -G "Ninja" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang

ninja -j 4
.\9_lab.exe

pause
