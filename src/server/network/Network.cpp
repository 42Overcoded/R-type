/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/
#include "Network.hpp"
#include "TestClassPlayer.hpp"

#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"

#include <iostream>
#include <sstream>


Network::Network()
{
    totalReceived = 0;
    cliMessage[500] = 0;
}

Network::~Network()
{
    ptrServSocket->close();

    delete ptrServSocket;
    delete ptrCliEndpoint;
    delete ptrError;
}

int Network::create_server(int portServer)
{
    boost::asio::io_context io_context;
    ptrServSocket = new boost::asio::ip::udp::socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portServer));

    ptrCliEndpoint = new boost::asio::ip::udp::endpoint(boost::asio::ip::udp::endpoint());
    ptrError = new boost::system::error_code(boost::system::error_code());

    return 0;
}

int Network::listen_info_from_clients(void)
{
    testPlayer *TestPlayer = new testPlayer();

    while (true) {
        totalReceived = ptrServSocket->receive_from(boost::asio::buffer(cliMessage), *ptrCliEndpoint, 0, *ptrError);
        //totalReceived = ptrServSocket->receive_from(boost::asio::buffer(TestPlayer, sizeof(*TestPlayer)), *ptrCliEndpoint, 0, *ptrError);

        if (ptrError->failed() == true && *ptrError != boost::asio::error::message_size) {
            std::cout << "Erreur de connexion: " << ptrError->message() << std::endl;
            break;
        }

        std::stringstream strstr;
        strstr << cliMessage;
        boost::archive::text_iarchive ia(strstr);
        ia >> *TestPlayer;

        if (TestPlayer != NULL) {
            std::cout << "-----------------------------------------------" << std::endl;
            std::cout << TestPlayer->name << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            std::cout << TestPlayer->level << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            std::cout << TestPlayer->hp << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            std::cout << TestPlayer->armor << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            std::cout << TestPlayer->drip << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            std::cout << TestPlayer->c << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            std::cout << TestPlayer->array << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
        } else {
            std::cout << "NULL" << std::endl;
        }
        break;
    }
    delete TestPlayer;
    return 0;
}
