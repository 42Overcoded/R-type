/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/

#include "Network.hpp"

#include <iostream>
#include <sstream>

Network::Network(std::string ipServer, int portServer)
{
    totalReceived = 0;
    cliMessage[500] = 0;
    _ipServer = ipServer;
    _portServer = portServer;

    ptrIOcontext = new boost::asio::io_context();
    ptrServSocket = new boost::asio::ip::udp::socket(*ptrIOcontext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portServer));
    ptrCliEndpoint = new boost::asio::ip::udp::endpoint();

    ptrIOcontextSend = new boost::asio::io_context();
    ptrServSocketSend = new boost::asio::ip::udp::socket(*ptrIOcontext, boost::asio::ip::udp::v4());
    ptrCliEndpointSend = new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(_ipServer), _portServer + 1);

    ptrError = new boost::system::error_code();
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

    if (ptrCliEndpoint != NULL)
        delete ptrCliEndpoint;
    if (ptrCliEndpointSend != NULL)
        delete ptrCliEndpointSend;

    if (ptrError != NULL)
        delete ptrError;

    
    if (ptrServSocket != NULL) {
        ptrServSocket->close();
        delete ptrServSocket;
    }
    if (ptrServSocketSend != NULL) {
        ptrServSocketSend->close();
        delete ptrServSocketSend;
    }
    //delete componentOUT.ptrToThisStruct;
}

void Network::listen_info_from_clients(registry *reg)
{
    while (true) {
        totalReceived = ptrServSocket->receive_from(boost::asio::buffer(&componentOUT, sizeof(componentOUT)), *ptrCliEndpoint, 0, *ptrError);

        if (ptrError->failed() == true && *ptrError != boost::asio::error::message_size) {
            std::cout << "Erreur de connexion: " << ptrError->message() << std::endl;
            break;
        }

        if (strcmp(componentOUT.nameStructToSend, "speed") == 0) {
            std::cout << "speed: " << componentOUT.speed.speedx << std::endl;
            entity_t entity1 = reg->spawn_entity();
            reg->register_component<ComponentOUT>();
            reg->add_component(entity1, componentOUT);
        }
        if (strcmp(componentOUT.nameStructToSend, "position") == 0) {
            std::cout << "position: " << componentOUT.position.x << std::endl;
            entity_t entity2 = reg->spawn_entity();
            reg->register_component<ComponentOUT>();
            reg->add_component(entity2, componentOUT);
        }
        if (strcmp(componentOUT.nameStructToSend, "sprite") == 0) {
            std::cout << "sprite: " << std::endl;
        }
        if (strcmp(componentOUT.nameStructToSend, "player") == 0) {
            std::cout << "player: " << componentOUT.player.id << std::endl;
            entity_t entity4 = reg->spawn_entity();
            reg->register_component<ComponentOUT>();
            reg->add_component(entity4, componentOUT);
        }
        if (strcmp(componentOUT.nameStructToSend, "bullet") == 0) {
            std::cout << "bullet: " << componentOUT.bullet.id << std::endl;
            entity_t entity5 = reg->spawn_entity();
            reg->register_component<ComponentOUT>();
            reg->add_component(entity5, componentOUT);
        }
        // if (strcmp(componentOUT.nameStructToSend, "tag") == 0) {
        //     std::cout << "tag: " << componentOUT.tag.tag << std::endl;
        //     entity_t entity6 = reg->spawn_entity();
        //     reg->register_component<ComponentOUT>();
        //     reg->add_component(entity6, componentOUT);
        // }
        if (strcmp(componentOUT.nameStructToSend, "health") == 0) {
            std::cout << "health: " <<componentOUT.health.health << std::endl;
            entity_t entity7 = reg->spawn_entity();
            reg->register_component<ComponentOUT>();
            reg->add_component(entity7, componentOUT);
        }
        if (strcmp(componentOUT.nameStructToSend, "damage") == 0) {
            std::cout << "damage: " << componentOUT.damage.damage << std::endl;
            entity_t entity8 = reg->spawn_entity();
            reg->register_component<ComponentOUT>();
            reg->add_component(entity8, componentOUT);
        }
        if (strcmp(componentOUT.nameStructToSend, "score") == 0) {
            std::cout << "score: " << componentOUT.score.score << std::endl;
            entity_t entity9 = reg->spawn_entity();
            reg->register_component<ComponentOUT>();
            reg->add_component(entity9, componentOUT);
        }
        if (strcmp(componentOUT.nameStructToSend, "drawable") == 0) {
            std::cout << "damage: " << componentOUT.drawable.drawable << std::endl;
            entity_t entity11 = reg->spawn_entity();
            reg->register_component<ComponentOUT>();
            reg->add_component(entity11, componentOUT);
        }
        if (strcmp(componentOUT.nameStructToSend, "control") == 0) {
            std::cout << "control: " << componentOUT.control.up << std::endl;
            entity_t entity12 = reg->spawn_entity();
            reg->register_component<ComponentOUT>();
            reg->add_component(entity12, componentOUT);
        }
        if (strcmp(componentOUT.nameStructToSend, "pattern") == 0) {
            std::cout << "pattern: " << componentOUT.pattern.pattern_index << std::endl;
            entity_t entity13 = reg->spawn_entity();
            reg->register_component<ComponentOUT>();
            reg->add_component(entity13, componentOUT);
        }
        if (strcmp(componentOUT.nameStructToSend, "hitbox") == 0) {
            std::cout << "hitbox: " << componentOUT.hitbox.height << std::endl;
            entity_t entity14 = reg->spawn_entity();
            reg->register_component<ComponentOUT>();
            reg->add_component(entity14, componentOUT);
        }
    }
}

int Network::send_info_to_client(void *strucToServer)
{
    ptrServSocketSend->send_to(boost::asio::buffer(strucToServer, sizeof(ComponentOUT)), *ptrCliEndpointSend, 0, *ptrError);
    return 0;
}
