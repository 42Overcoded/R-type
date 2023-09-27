/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/
#include "Network.hpp"

#include "testClassPlayer.hpp"

#include "boost/archive/text_iarchive.hpp"

#include <sstream>


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

    testPlayer *TestPlayer = new testPlayer; 
    size_t sizeTestPlayer = 500;

    std::string _name = "";

    // std::stringstream strstr;
    // boost::archive::text_iarchive ia{strstr};
    // ia >> TestPlayer;

    //boost::asio::buffer(TestPlayer, sizeTestPlayer)

    std::string info = "";
    char info2[500];

    while (true) {
        //totalReceived = ptrServSocket->receive_from(boost::asio::buffer(info2), *ptrCliEndpoint, 0, *ptrError);

        totalReceived = ptrServSocket->receive_from(boost::asio::buffer(TestPlayer, sizeof(*TestPlayer)), *ptrCliEndpoint, 0, *ptrError);

        if (ptrError->failed() == true && *ptrError != boost::asio::error::message_size) {
            std::cout << "Erreur de connexion: " << ptrError->message() << std::endl;
            break;
        }

        if (TestPlayer != NULL) {
            std::cout << "-----------------------------------------------" << std::endl;
            std::cout << TestPlayer->name << std::endl;
            //std::cout << "-----------------------------------------------" << std::endl;
            //std::cout << TestPlayer->level << std::endl;
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

    }
    delete TestPlayer;
    return 0;
}
