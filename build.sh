##
## EPITECH PROJECT, 2023
## R-type
## File description: build script for the project
## build
##

# fetch submodules
git submodule init
git submodule update

# build
cmake -B .Build -S .
cmake --build .Build
