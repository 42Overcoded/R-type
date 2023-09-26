/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/
#include "Network.hpp"

#include "testClassPlayer.hpp"

Network::Network()
{
    totalReceived = 0;
    cliMessage[500] = 0;
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
    // boost::asio::buffer(cliMessage)

    testPlayer *TestPlayer = new testPlayer(); 
    size_t sizeTestPlayer = 500;

    testPlayer *TestPlayer2 = NULL;

    // boost::asio::buffer(TestPlayer, sizeTestPlayer)
    while (true) {
        totalReceived = ptrServSocket->receive_from(boost::asio::buffer(TestPlayer, sizeTestPlayer), *ptrCliEndpoint, 0, *ptrError);
        std::cout << "bytes: " << sizeTestPlayer << std::endl;

        if (ptrError->failed() == true && *ptrError != boost::asio::error::message_size) {
            std::cout << "Erreur de connexion: " << ptrError->message() << std::endl;
            break;
        }
        std::cout << "Client: " << cliMessage << std::endl;
        std::cout << "ici" << std::endl;

        if (TestPlayer != NULL) {
            std::cout << TestPlayer->hp << std::endl;
            std::cout << "1" << std::endl;
            std::cout << TestPlayer->armor << std::endl;
            std::cout << "2" << std::endl;
            std::cout << TestPlayer->name << std::endl;
            std::cout << "3" << std::endl;
        } else
            std::cout << "NULL" << std::endl;

        if (TestPlayer2 != NULL) {
            std::cout << TestPlayer2->hp << std::endl;
            std::cout << "1" << std::endl;
            std::cout << TestPlayer2->name << std::endl;
            std::cout << "2" << std::endl;
        } else
            std::cout << "NULL" << std::endl;

        std::cout << "là" << std::endl;
    }
    delete TestPlayer;
    return 0;
}
