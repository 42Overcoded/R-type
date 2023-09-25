/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/
#include "Network.hpp"

Network::Network()
{
    totalReceived = 0;
}

Network::~Network()
{
    
}

int Network::create_server(int portServer)
{
    boost::asio::io_context io_context;
    ptrServSocket = std::make_shared<boost::asio::ip::udp::socket>(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portServer));

    ptrCliEndpoint = std::make_shared<boost::asio::ip::udp::endpoint>(boost::asio::ip::udp::endpoint());
    ptrError = std::make_shared<boost::system::error_code>(boost::system::error_code());

    return 0;
}

int Network::listen_info_from_clients(void)
{
    while (true) {
        totalReceived = ptrServSocket->receive_from(boost::asio::buffer(cliMessage), *ptrCliEndpoint, 0, *ptrError);

        if (ptrError->failed() == true && *ptrError != boost::asio::error::message_size) {
            std::cout << "Erreur de connexion: " << ptrError->message() << std::endl;
            break;
        }
        std::cout << "Client: " << cliMessage << std::endl;
    }
    return 0;
}
