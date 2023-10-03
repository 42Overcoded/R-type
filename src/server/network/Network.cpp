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
    std::cout << "Message perso" << std::endl;

    totalReceived = 0;
    cliMessage[500] = 0;
}

Network::~Network()
{
    if (ptrIOcontext != NULL) {
        ptrIOcontext->stop();
        delete ptrIOcontext;
    }

    if (ptrServSocket != NULL) {
        ptrServSocket->close();
        delete ptrServSocket;
    }
    if (ptrCliEndpoint != NULL)
        delete ptrCliEndpoint;
    if (ptrError != NULL)
        delete ptrError;
}

int Network::create_server(int portServer)
{
    ptrIOcontext = new boost::asio::io_context;
    ptrServSocket = new boost::asio::ip::udp::socket(*ptrIOcontext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portServer));

    ptrCliEndpoint = new boost::asio::ip::udp::endpoint;
    ptrError = new boost::system::error_code;

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
