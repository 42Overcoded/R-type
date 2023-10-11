/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystem
*/

#include <memory>
#include <optional>
#include <iostream>
#include <string>
#include "NetworkSystem.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "../ecs/ComponentsArray/Components/Components.hpp"
#include "Containers.hpp"

NetworkSystem::NetworkSystem(unsigned int serverPort)
{
    try
    {
        server_ = std::make_unique<UdpServer>(serverPort);
    } catch (std::exception &e) {
        std::cout << "Can't user server Port : " << serverPort << std::endl;
    }
}

NetworkSystem::~NetworkSystem()
{
}

void NetworkSystem::update(registry &reg)
{
    SparseArray<NetworkIn> &networkInArr   = reg.get_components<NetworkIn>();
    SparseArray<NetworkOut> &networkOutArr = reg.get_components<NetworkOut>();
    SparseArray<Control> &controlArr       = reg.get_components<Control>();

    manageInputs(reg);
    manageOutputs(reg);
}


void NetworkSystem::manageInputs(registry &reg)
{
    for (auto &client : server_->clients) {
        for (auto packet : client.second.availablePacket) {
            switch (packet.flags) {
                case flag::CONNECT:
                    manageConnectIn(reg, packet, client.first);
                    break;
                case flag::DISCONNECT:
                    manageDisconnectIn(reg, packet, client.first);
                    break;
                case flag::CONTROLLER:
                    manageControllerIn(reg, packet, client.first);
                    break;
                case flag::POSITION:
                    managePositionIn(reg, packet, client.first);
                    break;
                default:
                    break;
            }
        }
    }
}

void NetworkSystem::manageConnectIn(registry &reg, Packet &packet, std::string client)
{
    SparseArray<NetworkIn> &networkInArr   = reg.get_components<NetworkIn>();
    unsigned int clientId = server_->clients[client].id;

    for (unsigned int i; i < networkInArr.size(); i++) {
        if (networkInArr[i] != std::nullopt && networkInArr[i]->id == clientId) {
            
        }
    }
}

void NetworkSystem::manageDisconnectIn(registry &reg, Packet &packet, std::string client)
{
    SparseArray<NetworkIn> &networkInArr   = reg.get_components<NetworkIn>();
    unsigned int clientId = server_->clients[client].id;

    for (unsigned int i; i < networkInArr.size(); i++) {
        if (networkInArr[i] != std::nullopt && networkInArr[i]->id == clientId) {
            
        }
    }
}

void NetworkSystem::manageControllerIn(registry &reg, Packet &packet, std::string client)
{
    SparseArray<NetworkIn> &networkInArr   = reg.get_components<NetworkIn>();
    SparseArray<Control> &controlArr       = reg.get_components<Control>();
    unsigned int clientId = server_->clients[client].id;

    for (unsigned int i; i < networkInArr.size(); i++) {
        if (networkInArr[i] != std::nullopt && controlArr[i] != std::nullopt && networkInArr[i]->id == clientId) {
            ControllerContainer controllerContainer;
            controllerContainer.Unpack(packet.data);
            controlArr[i]->up = controllerContainer.up;
            controlArr[i]->down = controllerContainer.down;
            controlArr[i]->left = controllerContainer.left;
            controlArr[i]->right = controllerContainer.right;
            controlArr[i]->shoot = controllerContainer.shoot;
        }
    }
}

void NetworkSystem::managePositionIn(registry &reg, Packet &packet, std::string client)
{
    SparseArray<NetworkIn> &networkInArr   = reg.get_components<NetworkIn>();
    SparseArray<Position> &positionArr       = reg.get_components<Position>();
    unsigned int clientId = server_->clients[client].id;

    for (unsigned int i; i < networkInArr.size(); i++) {
        if (networkInArr[i] != std::nullopt && positionArr[i] != std::nullopt && networkInArr[i]->id == clientId) {
            PositionContainer positionContainer;
            positionContainer.Unpack(packet.data);
            positionArr[i]->x = positionContainer.x;
            positionArr[i]->y = positionContainer.y;
        }
    }
}

void NetworkSystem::manageOutputs(registry &reg)
{
    manageControllerOut(reg);
    managePositionOut(reg);
}

void NetworkSystem::manageControllerOut(registry &reg)
{
    SparseArray<NetworkOut> &networkOutArr = reg.get_components<NetworkOut>();
    SparseArray<Control> &controlArr       = reg.get_components<Control>();

    for (unsigned int i; i < networkOutArr.size(); i++) {
        if (networkOutArr[i] != std::nullopt && controlArr[i] != std::nullopt) {
            ControllerContainer data;
            data.up = controlArr[i]->up;
            data.down = controlArr[i]->down;
            data.left = controlArr[i]->left;
            data.right = controlArr[i]->right;
            data.shoot = controlArr[i]->shoot;
            server_->sendToAll(flag::CONTROLLER, data.Pack());
        }
    }
}

void NetworkSystem::managePositionOut(registry &reg)
{
    SparseArray<NetworkOut> &networkOutArr = reg.get_components<NetworkOut>();
    SparseArray<Position> &positionArr       = reg.get_components<Position>();

    for (unsigned int i; i < networkOutArr.size(); i++) {
        if (networkOutArr[i] != std::nullopt && positionArr[i] != std::nullopt) {
            PositionContainer data;
            data.x = positionArr[i]->x;
            data.y = positionArr[i]->y;
            server_->sendToAll(flag::POSITION, data.Pack());
        }
    }
}
