mkdir build
cd build

cmake .. -G "Ninja" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang

ninja -j 4
.\10_lab.exe

pause
