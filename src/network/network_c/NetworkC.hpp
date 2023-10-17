/*
** EPITECH PROJECT, 2023
** CLIENT
** File description:
** CLIENT
*/
#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <boost/asio.hpp>

class NetworkC {
    private:
        boost::asio::io_context *ptrIOcontext;
        boost::asio::ip::udp::endpoint *ptrServEndpoint;
        boost::asio::ip::udp::socket *ptrCliSocket;
        boost::asio::io_context *ptrIOcontextReceive;
        boost::asio::ip::udp::socket *ptrCliSocketReceive;
        boost::asio::ip::udp::endpoint *ptrServEndpointReceive;
        boost::system::error_code *ptrError;
        std::string _ipServer;
        int _portServer;
        size_t totalReceived;
    public:
        NetworkC(std::string ipServer, int portServer = 4242);
        ~NetworkC();
        int send_info_to_server(void *strucToServer);
        int listen_info_from_server(void);
};

#endif
