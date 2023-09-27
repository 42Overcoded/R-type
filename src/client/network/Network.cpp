/*
** EPITECH PROJECT, 2023
** CLIENT
** File description:
** CLIENT
*/
#include "Network.hpp"
#include "testClassPlayer.hpp"

#include <sstream>

#include <boost/archive/text_iarchive.hpp>

#include <iostream>

#include <boost/archive/text_oarchive.hpp>


Network::Network()
{

};

Network::~Network()
{

}

int Network::create_client(std::string ipServer, int portServer)
{
    boost::asio::io_context io_context;

    ptrCliSocket = std::make_shared<boost::asio::ip::udp::socket>(io_context, boost::asio::ip::udp::v4());
    ptrServEndpoint = std::make_shared<boost::asio::ip::udp::endpoint>(boost::asio::ip::address::from_string(ipServer), portServer);

    ptrError = std::make_shared<boost::system::error_code>();

    return 0;
}

int Network::send_info_to_server(void *object_player, void *object_command)
{
    testPlayer *TestPlayer = new testPlayer;

    TestPlayer->name = "serge";
    TestPlayer->level = "skeleton";
    TestPlayer->hp = 34;
    TestPlayer->armor = 153;
    TestPlayer->drip = true;
    TestPlayer->c = 'E';
    strcpy(TestPlayer->array, "array fonctionne");

    // std::stringstream strstr;
    // boost::archive::text_oarchive oa(strstr);
    // oa << *TestPlayer;


    ptrCliSocket->send_to(boost::asio::buffer(TestPlayer, sizeof(*TestPlayer)), *ptrServEndpoint, 0, *ptrError);
    //ptrCliSocket->send_to(boost::asio::buffer(strstr.str()), *ptrServEndpoint, 0, *ptrError);

    delete TestPlayer;
    return 0;
}
