/*
** EPITECH PROJECT, 2023
** CLIENT
** File description:
** CLIENT
*/

#include <iostream>
#include <sstream>
#include "NetworkC.hpp"
#include "NetworkComponent.hpp"
#include "../ecs/ComponentsArray/Components/Components.hpp"

NetworkC::NetworkC(std::string ipServer, int portServer)
{
    _ipServer = ipServer;
    _portServer = portServer;

    ptrIOcontext = new boost::asio::io_context;
    ptrCliSocket = new boost::asio::ip::udp::socket(*ptrIOcontext, boost::asio::ip::udp::v4());
    ptrServEndpoint = new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(_ipServer), _portServer);

    ptrIOcontextReceive = new boost::asio::io_context;
    ptrCliSocketReceive = new boost::asio::ip::udp::socket(*ptrIOcontextReceive, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portServer + 1));
    ptrServEndpointReceive = new boost::asio::ip::udp::endpoint;

    ptrError = new boost::system::error_code;
}

NetworkC::~NetworkC()
{
    if (ptrIOcontext != NULL) {
        ptrIOcontext->stop();
        delete ptrIOcontext;
    }
    if (ptrIOcontextReceive != NULL) {
        ptrIOcontextReceive->stop();
        delete ptrIOcontextReceive;
    }

    if (ptrCliSocket != NULL) {
        ptrCliSocket->close();
        delete ptrCliSocket;
    }
    if (ptrCliSocketReceive != NULL) {
        ptrCliSocketReceive->close();
        delete ptrCliSocketReceive;
    }
    if (ptrServEndpoint != NULL)
        delete ptrServEndpoint;
    if (ptrServEndpointReceive != NULL)
        delete ptrServEndpointReceive;

    if (ptrError != NULL)
        delete ptrError;
}

int NetworkC::send_info_to_server(void *strucToServer)
{
    ptrCliSocket->send_to(boost::asio::buffer(strucToServer, sizeof(ComponentOUT)), *ptrServEndpoint, 0, *ptrError);
    return 0;
}

int NetworkC::listen_info_from_server(registry *reg)
{
    ComponentOUT componentOUT;

    while (true) {
        totalReceived = ptrCliSocketReceive->receive_from(boost::asio::buffer(&componentOUT, sizeof(componentOUT)), *ptrServEndpointReceive, 0, *ptrError);

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
    return 0;
}

