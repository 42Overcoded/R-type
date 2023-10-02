/*
** EPITECH PROJECT, 2023
** CLIENT
** File description:
** CLIENT
*/
#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <boost/asio.hpp>

class Network {
    private:
        boost::asio::io_context *ptrIOcontext;
        boost::asio::ip::udp::endpoint *ptrServEndpoint;
        boost::asio::ip::udp::socket *ptrCliSocket;
        boost::system::error_code *ptrError;
    public:
        Network();
        ~Network();
        int create_client(std::string ipServer, int portServer = 4242);
        int send_info_to_server(void *object_player = NULL, void *object_command = NULL);
};

#endif
