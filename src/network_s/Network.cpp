/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/

#include "Network.hpp"
#include "NetworkComponents.hpp"
#include "../ecs/ComponentsArray/Components/Components.hpp"

#include <iostream>
#include <sstream>

Network::Network(std::string ipServer, int portServer)
{
    totalReceived = 0;
    cliMessage[500] = 0;
    _ipServer = ipServer;
    _portServer = portServer;

    ptrIOcontext = new boost::asio::io_context;
    ptrServSocket = new boost::asio::ip::udp::socket(*ptrIOcontext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portServer));
    ptrCliEndpoint = new boost::asio::ip::udp::endpoint;

    ptrIOcontextSend = new boost::asio::io_context;
    ptrServSocketSend = new boost::asio::ip::udp::socket(*ptrIOcontext, boost::asio::ip::udp::v4());
    ptrCliEndpointSend = new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(_ipServer), _portServer + 1);

    ptrError = new boost::system::error_code;
}

Network::~Network()
{
    if (ptrIOcontext != NULL) {
        ptrIOcontext->stop();
        delete ptrIOcontext;
    }
    if (ptrIOcontextSend != NULL) {
        ptrIOcontextSend->stop();
        delete ptrIOcontextSend;
    }

    if (ptrServSocket != NULL) {
        ptrServSocket->close();
        delete ptrServSocket;
    }
    if (ptrServSocketSend != NULL) {
        ptrServSocketSend->close();
        delete ptrServSocketSend;
    }

    if (ptrCliEndpoint != NULL)
        delete ptrCliEndpoint;
    if (ptrCliEndpointSend != NULL)
        delete ptrCliEndpointSend;

    if (ptrError != NULL)
        delete ptrError;
}

int Network::listen_info_from_clients(void)
{
    ComponentOUT componentOUT;

    while (true) {
        totalReceived = ptrServSocket->receive_from(boost::asio::buffer(&componentOUT, sizeof(componentOUT)), *ptrCliEndpoint, 0, *ptrError);

        if (ptrError->failed() == true && *ptrError != boost::asio::error::message_size) {
            std::cout << "Erreur de connexion: " << ptrError->message() << std::endl;
            break;
        }

        if (strcmp(componentOUT.nameStructToSend, "speed") == 0)
            std::cout << "speed: " << componentOUT.speed.speedx << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "position") == 0)
            std::cout << "position: " << componentOUT.position.x << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "sprite") == 0)
            std::cout << "sprite: " << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "player") == 0)
            std::cout << "player: " << componentOUT.player.id << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "bullet") == 0)
            std::cout << "bullet: " << componentOUT.bullet.id << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "tag") == 0)
            std::cout << "tag: " << componentOUT.tag.tag << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "health") == 0)
            std::cout << "health: " <<componentOUT.health.health << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "damage") == 0)
            std::cout << "damage: " << componentOUT.damage.damage << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "score") == 0)
            std::cout << "score: " << componentOUT.score.score << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "text") == 0)
            std::cout << "text: " << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "drawable") == 0)
            std::cout << "damage: " << componentOUT.drawable.drawable << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "control") == 0)
            std::cout << "control: " << componentOUT.control.up << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "pattern") == 0)
            std::cout << "pattern: " << componentOUT.pattern.pattern_index << std::endl;
        if (strcmp(componentOUT.nameStructToSend, "hitbox") == 0)
            std::cout << "hitbox: " << componentOUT.hitbox.height << std::endl;
    }
    return 0;
}

int Network::send_info_to_client(void *strucToServer)
{
    ptrServSocketSend->send_to(boost::asio::buffer(strucToServer, sizeof(ComponentOUT)), *ptrCliEndpointSend, 0, *ptrError);
    return 0;
}
