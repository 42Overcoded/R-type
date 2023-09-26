/*
** EPITECH PROJECT, 2023
** CLIENT
** File description:
** CLIENT
*/
#include "Network.hpp"
#include "testClassPlayer.hpp"

Network::Network()
{

};

Network::~Network()
{

}

int Network::create_client(std::string ipServer, int portServer)
{
    boost::asio::io_context io_context;

    ptrCliSocket = std::make_shared<boost::asio::ip::udp::socket>(boost::asio::ip::udp::socket(io_context, boost::asio::ip::udp::v4()));
    ptrServEndpoint = std::make_shared<boost::asio::ip::udp::endpoint>(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ipServer), portServer));

    return 0;
}

int Network::send_info_to_server(void *object_player, void *object_command)
{
    std::string playerCommand = "Commande Joueur";

    testPlayer *TestPlayer = new testPlayer();

    TestPlayer->hp = 34;
    TestPlayer->armor = 155;
    TestPlayer->name = "serge";

    // &TestPlayer, sizeof(TestPlayer)
    std::cout << "bytes: " << sizeof(*TestPlayer) << std::endl;
    ptrCliSocket->send_to(boost::asio::buffer(TestPlayer, sizeof(*TestPlayer)), *ptrServEndpoint);
    return 0;
}
