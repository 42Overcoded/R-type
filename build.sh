##
## EPITECH PROJECT, 2023
## R-type
## File description:
## build
##

mkdir build > /dev/null 2>&1
cd build > /dev/null 2>&1
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j
cd - > /dev/null 2>&1