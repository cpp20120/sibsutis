# Remove build folder if it exists and recreate it
if (Test-Path -Path "build") {
    Remove-Item -Path "build" -Recurse -Force
    Write-Host "Removed existing build folder"
}

mkdir build
cd build

cmake .. -G "Ninja" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang

ninja -j 4
.\src\SAOD.exe

pause