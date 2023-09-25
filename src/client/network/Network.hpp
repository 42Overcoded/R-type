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
    private:
        std::shared_ptr<boost::asio::ip::udp::endpoint> ptrServEndpoint;
        std::shared_ptr<boost::asio::ip::udp::socket> ptrCliSocket;
    public:
        Network();
        ~Network();
        int create_client(std::string ipServer, int portServer = 4242);
        int send_info_to_server(void *object_player = NULL, void *object_command = NULL);
};

#endif
