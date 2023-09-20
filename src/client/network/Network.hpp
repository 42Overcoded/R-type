/*
** EPITECH PROJECT, 2023
** CLIENT
** File description:
** CLIENT
*/
#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <iostream>
#include <boost/asio.hpp>

class Network {
    public:
        Network();
        ~Network();
        int create_client(void);
};

#endif
