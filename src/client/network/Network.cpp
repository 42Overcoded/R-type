/*
** EPITECH PROJECT, 2023
** CLIENT
** File description:
** CLIENT
*/
#include "Network.hpp"
#include "TestClassPlayer.hpp"

#include <iostream>
#include <sstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


Network::Network()
{

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

int Network::create_client(std::string ipServer, int portServer)
{
    ptrIOcontext = new boost::asio::io_context;

    ptrCliSocket = new boost::asio::ip::udp::socket(*ptrIOcontext, boost::asio::ip::udp::v4());
    ptrServEndpoint = new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ipServer), portServer);

    ptrError = new boost::system::error_code;

    return 0;
}

int Network::send_info_to_server(void *object_player, void *object_command)
{
    testPlayer *TestPlayer = new testPlayer();

    TestPlayer->name = "serge";
    TestPlayer->level = "skeleton";
    TestPlayer->hp = 34;
    TestPlayer->armor = 153;
    TestPlayer->drip = true;
    TestPlayer->c = 'E';
    strcpy(TestPlayer->array, "array fonctionne");


    std::stringstream strstr;
    boost::archive::text_oarchive oa(strstr);
    oa << *TestPlayer;


    //ptrCliSocket->send_to(boost::asio::buffer(TestPlayer, sizeof(*TestPlayer)), *ptrServEndpoint, 0, *ptrError);
    ptrCliSocket->send_to(boost::asio::buffer(strstr.str()), *ptrServEndpoint, 0, *ptrError);


    delete TestPlayer;
    return 0;
}
