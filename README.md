# R-type

![GitHub](https://img.shields.io/badge/github-%23121011.svg?logo=github)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?logo=c%2B%2B)
![SFML](https://img.shields.io/badge/SFML-2.5.1-green)
![Boost](https://img.shields.io/badge/Boost-1.76.0-blue)

A multiplayer R-type like game made in C++.  
This project is part of the Epitech third year curriculum.

## Summary

- [R-type](#r-type)
  - [Summary](#summary)
  - [Official supported platforms](#official-supported-platforms)
  - [How to build application](#how-to-build-application)
    - [Linux](#linux)
      - [Dependencies](#dependencies)
      - [Build with build.sh](#build-with-buildsh)
      - [Build with cmake](#build-with-cmake)
      - [Build output](#build-output)
    - [Windows](#windows)
  - [Build installers and packages](#build-installers-and-packages)
    - [Using build.sh](#using-buildsh)
  - [How to run](#how-to-run)
  - [Documentation](#documentation)
  - [Authors](#authors)
  - [License](#license)
  - [Acknowledgments](#acknowledgments)

## Official supported platforms

- [X] ![Fedora](https://img.shields.io/badge/Fedora-294172?logo=fedora&logoColor=white "Fedora")
- [X] ![Linux Mint](https://img.shields.io/badge/Linux%20Mint-87CF3E?&logo=Linux%20Mint&logoColor=white "Linux Mint")
- [X] ![Windows 11](https://img.shields.io/badge/Windows%2011-%230079d5.svg?logo=Windows%2011&logoColor=white "Windows 11")

## Requirements

c++20 compiler or vscode compiler

## How to build application

### Linux

#### Dependencies

On debian based distributions :

```bash
sudo apt-get install freeglut3-dev libfreetype6-dev libx11-dev libxrandr-dev libudev-dev libgl1-mesa-dev libflac-dev libogg-dev libvorbis-dev libvorbisenc2 libvorbisfile3 libopenal-dev libpthread-stubs0-dev xorg-dev
```

#### Build with build.sh

```bash
./build.sh
```

#### Build with cmake

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

#### Build output

You can now find the executables at the root of the repository.

- r type server : `r-type_server`
- r type client : `r-type_client`

### Windows

Using **cmake-gui.exe** or **Visual Studio**.

## Build installers and packages

### Using build.sh

```bash
./build.sh -p
```

This will create a `build` directory and generate the installers and packages in it.

## How to run

Before running the application, you need to [build](#build) it.
Or you can download the appropriate release for your platform on the last release tab of the [project](https://github.com/42Overcoded/R-type).

```bash
./r-type_server [port]
```

Port is an optional argument, default value is 4242.

```bash
./r-type_client [serverPort serverIp]
```

Server port and server ip are optional arguments, default values are 4242 and 127.0.0.1 (localhost).

## Documentation

You can find the documentation on the [website](https://42overcoded.github.io/R-type/html/html/index.html).
Or you can generate it yourself with doxygen :

```bash
cd docs
doxygen Doxyfile
```

Generated doc can be found in `docs/html`.

## Authors

- **Sergey Borisenko**
- **Macéo JALBERT**
- **Florian AZEMA**
- **Mickael PEIRETO**
- **Julien VIGNAU-ESPINE**

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

- [CMake](https://cmake.org/)
- [SFML](https://www.sfml-dev.org/)
- [Boost](https://www.boost.org/)
