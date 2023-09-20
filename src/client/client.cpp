/*
** EPITECH PROJECT, 2023
** network
** File description:
** client
*/
#include <iostream>
#include "network/Network.hpp"

int main() {
    //std::cout << "Hello, i'm the client function" << std::endl;
    Network network;

    network.create_client();
    return 0;
}
