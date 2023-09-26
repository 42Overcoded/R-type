##
## EPITECH PROJECT, 2023
## R-type
## File description:
## build
##

mkdir .Build > /dev/null 2>&1
cd .Build > /dev/null 2>&1
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd - > /dev/null 2>&1