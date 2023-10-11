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
        std::string _ipServer;
        int _portServer;
    public:
        Network(std::string ipServer, int portServer = 4242);
        ~Network();
        int send_info_to_server(void *strucToServer);
};

#endif
