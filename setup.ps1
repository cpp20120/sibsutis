function Install-VisualStudio {
    try {
      Invoke-WebRequest -Uri "https://aka.ms/vs/17/release/vs_Community.exe" -OutFile "vs_Community.exe"
      Start-Process -FilePath "vs_Community.exe" -ArgumentList "/InstallSelect=VisualStudio.DesktopDevelopment.C++/VisualStudio.DesktopDevelopment.NET" -Wait
      Remove-Item "vs_Community.exe"
    } catch {
      Write-Error "Error installing Visual Studio: $($_.Exception.Message)"
      exit
    }
  }
  
  function Install-Tools {
    try {
      Invoke-WebRequest -Uri "https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-windows-x86_64.zip" -OutFile "cmake.zip"
      Expand-Archive -Path "cmake.zip" -DestinationPath "C:\Program Files\CMake"
      Remove-Item "cmake.zip"
      $env:Path += ";C:\Program Files\CMake\bin"
  
      Invoke-WebRequest -Uri "https://github.com/ninja-build/ninja/releases/download/v1.11.1/ninja-win.zip" -OutFile "ninja.zip"
      Expand-Archive -Path "ninja.zip" -DestinationPath "C:\Program Files\Ninja"
      Remove-Item "ninja.zip"
      $env:Path += ";C:\Program Files\Ninja"
  
      Invoke-WebRequest -Uri "https://www.stack.nl/~dimitri/doxygen/download.html" -OutFile "doxygen-1.9.6.zip"
      Expand-Archive -Path "doxygen-1.9.6.zip" -DestinationPath "C:\Program Files\Doxygen"
      Remove-Item "doxygen-1.9.6.zip"
  
      Invoke-WebRequest -Uri "https://releases.llvm.org/18.1.0/LLVM-18.1.0-win64.exe" -OutFile "llvm-18.1.0-win64.exe"
      Start-Process -FilePath "llvm-18.1.0-win64.exe" -ArgumentList "/S" -Wait
      Remove-Item "llvm-18.1.0-win64.exe"
  
      $env:Path += ";C:\Program Files\LLVM\bin"
  
      Invoke-WebRequest -Uri "https://www.sqlite.org/2023/sqlite-autoconf-3400000.zip" -OutFile "sqlite.zip"
      Expand-Archive -Path "sqlite.zip" -DestinationPath "C:\Program Files\SQLite"
      Remove-Item "sqlite.zip"
    } catch {
      Write-Error "Error installing Tools: $($_.Exception.Message)"
      exit
    }
  }
  
  function Install-Vcpkg {
    try {
      Invoke-WebRequest -Uri "https://github.com/microsoft/vcpkg/archive/refs/heads/master.zip" -OutFile "vcpkg.zip"
      Expand-Archive -Path "vcpkg.zip" -DestinationPath "C:\vcpkg"
      Remove-Item "vcpkg.zip"
  
      cd "C:\vcpkg"
  
      .\bootstrap-vcpkg.bat
      .\vcpkg integrate install
      .\vcpkg install sfml sdl2 sdl2-image gtest
    } catch {
      Write-Error "Error installing Vcpkg: $($_.Exception.Message)"
      exit
    }
  }
  
  function Install-Git {
    try {
      Invoke-WebRequest -Uri "https://github.com/git-for-windows/git/releases/download/v2.47.0.windows.1/Git-2.47.0-64-bit.exe" -OutFile "Git-2.47.0-64-bit.exe"
      Start-Process -FilePath "Git-2.47.0-64-bit.exe" -ArgumentList "/S" -Wait
      Remove-Item "Git-2.47.0-64-bit.exe"
      $env:Path += ";C:\Program Files\Git\bin"
    } catch {
      Write-Error "Error installing Git: $($_.Exception.Message)"
      exit
    }
  }
  
  Install-VisualStudio
  Install-Tools
  Install-Vcpkg
  Install-Git
  
  Write-Host "Installation complete!"
  