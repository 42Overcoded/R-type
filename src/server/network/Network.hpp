/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** network
*/
#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <iostream>
#include <boost/asio.hpp>

class Network {
    public:
        Network();
        ~Network();
        int create_server(void);
};

#endif /* !NETWORK_HPP_ */
