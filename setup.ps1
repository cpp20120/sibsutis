# Function to install Visual Studio with C++ and C# components
function Install-VisualStudio {
    # Download Visual Studio Installer
    Invoke-WebRequest -Uri "https://aka.ms/vs/17/release/vs_Community.exe" -OutFile "vs_Community.exe"
    # Run the installer with specified components
    Start-Process -FilePath "vs_Community.exe" -ArgumentList "/InstallSelect=VisualStudio.DesktopDevelopment.C++/VisualStudio.DesktopDevelopment.NET" -Wait
    # Remove installer
    Remove-Item "vs_Community.exe"
   }
   
   # Function to install CMake, Ninja, Doxygen, Clang, Clang-format, and SQLite
   function Install-Tools {
    # Install CMake
    Invoke-WebRequest -Uri "https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-windows-x86_64.zip" -OutFile "cmake.zip"
    Expand-Archive -Path "cmake.zip" -DestinationPath "C:\Program Files\CMake"
    Remove-Item "cmake.zip"
    # Add CMake to PATH
    $env:Path += ";C:\Program Files\CMake\bin"
   
    # Install Ninja
    Invoke-WebRequest -Uri "https://github.com/ninja-build/ninja/releases/download/v1.11.1/ninja-win.zip" -OutFile "ninja.zip"
    Expand-Archive -Path "ninja.zip" -DestinationPath "C:\Program Files\Ninja"
    Remove-Item "ninja.zip"
    # Add Ninja to PATH
    $env:Path += ";C:\Program Files\Ninja"
   
    # Install Doxygen
    Invoke-WebRequest -Uri "https://www.stack.nl/~dimitri/doxygen/download.html" -OutFile "doxygen-1.9.6.zip"
    Expand-Archive -Path "doxygen-1.9.6.zip" -DestinationPath "C:\Program Files\Doxygen"
    Remove-Item "doxygen-1.9.6.zip"
   
    # Install Clang & Clang-format (version 18.1.0)
    Invoke-WebRequest -Uri "https://releases.llvm.org/18.1.0/LLVM-18.1.0-win64.exe" -OutFile "llvm-18.1.0-win64.exe"
    Start-Process -FilePath "llvm-18.1.0-win64.exe" -ArgumentList "/S" -Wait
    Remove-Item "llvm-18.1.0-win64.exe"
    # Add LLVM bin to PATH
    $env:Path += ";C:\Program Files\LLVM\bin"
   
    # Install SQLite
    Invoke-WebRequest -Uri "https://www.sqlite.org/2023/sqlite-autoconf-3400000.zip" -OutFile "sqlite.zip"
    Expand-Archive -Path "sqlite.zip" -DestinationPath "C:\Program Files\SQLite"
    Remove-Item "sqlite.zip"
   }
   
   # Function to install vcpkg and desired libraries
   function Install-Vcpkg {
    # Download vcpkg
    Invoke-WebRequest -Uri "https://github.com/microsoft/vcpkg/archive/refs/heads/master.zip" -OutFile "vcpkg.zip"
    Expand-Archive -Path "vcpkg.zip" -DestinationPath "C:\vcpkg"
    Remove-Item "vcpkg.zip"
    # Navigate to vcpkg directory
    cd "C:\vcpkg"
    # Bootstrap vcpkg
    .\bootstrap-vcpkg.bat
    # Install libraries using vcpkg
    .\vcpkg install sfml sdl2 sdl2_image
   }
   
   # Install Visual Studio
   Install-VisualStudio
   
   # Install tools
   Install-Tools
   
   # Install vcpkg and libraries
   Install-Vcpkg
   
   # Display message
   Write-Host "Installation complete!"
   