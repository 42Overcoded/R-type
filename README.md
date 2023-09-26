# R-type

A R-type like game made in C++.

## Summary

- [R-type](#r-type)
  - [Summary](#summary)
  - [Official supported platforms](#official-supported-platforms)
  - [How to build](#how-to-build)
    - [Linux](#linux)
    - [Dependencies](#dependencies)
    - [Build](#build)
    - [Windows](#windows)
  - [How to run](#how-to-run)
  - [Authors](#authors)
  - [License](#license)
  - [Acknowledgments](#acknowledgments)

## Official supported platforms

- [x] Fedora
- [x] Linux Mint
- [x] Windows 11

## How to build

### Linux

### Dependencies

On debian based distributions :

```bash
sudo apt-get install freeglut3-dev libfreetype6-dev libx11-dev libxrandr-dev libudev-dev libgl1-mesa-dev libflac-dev libogg-dev libvorbis-dev libvorbisenc2 libvorbisfile3 libopenal-dev libpthread-stubs0-dev xorg-dev
```

### Build

```bash
./build.sh
```

You can now find the executable in the `build` folder.

- r type server : `build/server/r-type_server`
- r type client : `build/client/r-type_client`

### Windows

Using **cmake-gui.exe**

## How to run

```bash
./r-type_server
./r-type_client
```

## Authors

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
