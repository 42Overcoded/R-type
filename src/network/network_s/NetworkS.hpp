/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** network
*/
#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <boost/asio.hpp>
#include "../ecs/Registry.hpp"
#include "NetworkComponent.hpp"

class NetworkS {
    private:
        boost::asio::io_context *ptrIOcontext;
        boost::asio::ip::udp::socket *ptrServSocket;
        boost::asio::ip::udp::endpoint *ptrCliEndpoint;

        boost::asio::io_context *ptrIOcontextSend;
        boost::asio::ip::udp::socket *ptrServSocketSend;
        boost::asio::ip::udp::endpoint *ptrCliEndpointSend;
        boost::system::error_code *ptrError;

        std::string _ipServer;
        int _portServer;
        char cliMessage[1000];
        size_t totalReceived;

        ComponentOUT componentOUT;
    public:
        NetworkS(std::string ipServer, int portServer = 4242);
        ~NetworkS();
        void listen_info_from_clients(registry *reg);
        int send_info_to_client(void *strucToServer);
};

#endif /* !NETWORK_HPP_ */
