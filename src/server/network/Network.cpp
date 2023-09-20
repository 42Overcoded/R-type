/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/
#include "Network.hpp"

Network::Network()
{

}

Network::~Network()
{
    
}

int Network::create_server(void)
{
    char cliMessage[500];
    size_t totalReceived = 0;
    boost::asio::io_context io_context;
    boost::asio::ip::udp::socket servSock(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 4242));

    boost::asio::ip::udp::endpoint client_endpoint;
    boost::system::error_code erc;
    while (true) {
        totalReceived = servSock.receive_from(boost::asio::buffer(cliMessage), client_endpoint, 0, erc);

        if (erc.failed() == true && erc != boost::asio::error::message_size) {
            std::cout << "Erreur de connexion: " << erc.message() << std::endl;
            break;
        }
        std::cout << "Client: " << cliMessage << std::endl;
    }

    return 0;
}
