#!/bin/bash

install_fedora () {
 sudo dnf5 install curl wget
 sudo rpm --import https://packages.microsoft.com/keys/microsoft.asc
 echo -e "[code]\nname=Visual Studio Code\nbaseurl=https://packages.microsoft.com/yumrepos/vscode\nenabled=1\ngpgcheck=1\ngpgkey=https://packages.microsoft.com/keys/microsoft.asc" | sudo tee /etc/yum.repos.d/vscode.repo > /dev/null
 sudo dnf install dnf5
 sudo dnf5 install -y  gcc lang  cmake  ninja-build  make  clang-tools-extra qt6-qtbase-devel SFML SFML-devel SDL2-devel SDL2_image-devel dotnet-sdk-8.0 dotnet-runtime-8.0 sqlite sqlite-devel code doxygen gtest-devel python3 python3-pip 
}

install_debian() {
 sudo apt install curl wget
 curl -fsSL https://packages.microsoft.com/keys/microsoft.asc | gpg -dearmor > microsoft.gpg
 sudo install -o root -g root -m 644 microsoft.gpg /etc/apt/keyrings/microsoft-archive-keyring.gpg

 sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/keyrings/microsoft-archive-keyring.gpg] https://packages.microsoft.com/repos/vscode stable main" > /etc/apt/sources.list.d/vscode.list'
 sudo apt update
 sudo apt install -y  gcc  clang  cmake  ninja-build  make  clang-format clang-tools lld doxygen qt6-base-dev  libsfml-dev libsdl2-dev libsdl2-image-dev dotnet-sdk  sqlite3  code libgtest-dev python3 python3-pip 
}

install_arch () {
 sudo pacman -Syu wget curl gcc  clang  cmake  ninja  make  clang-format  qt6-base  sfml sdl2 sdl2_image dotnet-sdk  sqlite  code doxygen gtest python python-pip 
}

install_macos () {
 if ! command -v brew > /dev/null; then
  echo "Homebrew не найден. Устанавливаю Homebrew..."
  /bin/bash -c "(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
 fi

 xcode-select -install
 brew install  curl wget gcc  llvm cmake  ninja  qt  sfml sdl2_image sdl2 sqlite googletest doxygen  dotnet-sdk python python-pip –cask visual-studio-code 

 echo "Установка завершена!"
}

setup_vscode_linux() {
 wget https://gitlab.com/cppshizoid/dotfiles/-/raw/main/vscode/BasicC++.code-profile -P  $HOME/.config/Code/User/profiles
}

setup_vscode_macos() {
 wget https://gitlab.com/cppshizoid/dotfiles/-/raw/main/vscode/BasicC++.code-profile -P $HOME/Library/Application\ Support/Code/User/profiles
}


if [ -x "$(command -v dnf)" ]; then
 install_fedora
 setup_vscode
elif [ -x "$(command -v apt-get)" ]; then
 install_debian
 setup_vscode
elif [ -x "$(command -v pacman)" ]; then
 install_arch
 setup_vscode
elif [ -x "$(command -v brew)" ]; then
 install_macos
 setup_vscode
else
 echo "Не удалось определить операционную систему. Используйте: fedora|debian|arch|macos"
 exit 1
fi

echo "Установка завершена!"
