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

    network.create_client("10.15.193.252", 4242);
    network.send_info_to_server();
    return 0;
}
