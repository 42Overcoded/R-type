/*
** EPITECH PROJECT, 2023
** CLIENT
** File description:
** CLIENT
*/

#include <iostream>
#include <sstream>
#include "Network.hpp"
#include "NetworkComponents.hpp"
#include "../ecs/ComponentsArray/Components/Components.hpp"

Network::Network(std::string ipServer, int portServer)
{
    _ipServer = ipServer;
    _portServer = portServer;

    ptrIOcontext = new boost::asio::io_context;

    ptrCliSocket = new boost::asio::ip::udp::socket(*ptrIOcontext, boost::asio::ip::udp::v4());
    ptrServEndpoint = new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(_ipServer), _portServer);

    ptrError = new boost::system::error_code;
}

Network::~Network()
{
    if (ptrIOcontext != NULL) {
        ptrIOcontext->stop();
        delete ptrIOcontext;
    }

    if (ptrCliSocket != NULL) {
        ptrCliSocket->close();
        delete ptrCliSocket;
    }
    if (ptrServEndpoint != NULL)
        delete ptrServEndpoint;
    if (ptrError != NULL)
        delete ptrError;
}

int Network::send_info_to_server(void *strucToServer)
{
    ptrCliSocket->send_to(boost::asio::buffer(strucToServer, sizeof(ComponentOUT)), *ptrServEndpoint, 0, *ptrError);
    return 0;
}
