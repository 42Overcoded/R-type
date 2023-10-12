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

NetworkSystem::NetworkSystem(unsigned int serverPort, std::string serverIp)
{
    try
    {
        server_ = std::make_unique<UdpClient>(serverPort, serverIp);
    } catch (std::exception &e) {
        std::cout << "Can't user server Port : " << serverPort << std::endl;
    }
}

NetworkSystem::~NetworkSystem()
{
}

void NetworkSystem::update(registry &reg)
{
    std::cout << "running server" << std::endl;
    server_->run();
    std::cout << "managing inputs" << std::endl;
    manageInputs(reg);
    std::cout << "managing outputs" << std::endl;
    manageOutputs(reg);
    std::cout << "end of update" << std::endl;
}


void NetworkSystem::manageInputs(registry &reg)
{
    for (auto packet : server_->server.availablePacket) {
        switch (packet.flags) {
            case flag::CONNECT:
                manageConnectIn(reg, packet);
                break;
            case flag::DISCONNECT:
                manageDisconnectIn(reg, packet);
                break;
            case flag::CONTROLLER:
                manageControllerIn(reg, packet);
                break;
            case flag::POSITION:
                managePositionIn(reg, packet);
                break;
            default:
                break;
        }
    }
}

void NetworkSystem::manageConnectIn(registry &reg, Packet &packet)
{
    SparseArray<NetworkIn> &networkInArr   = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++) {
        if (networkInArr[i] != std::nullopt) {
            
        }
    }
}

void NetworkSystem::manageDisconnectIn(registry &reg, Packet &packet)
{
    SparseArray<NetworkIn> &networkInArr   = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++) {
        if (networkInArr[i] != std::nullopt) {
            
        }
    }
}

void NetworkSystem::manageControllerIn(registry &reg, Packet &packet)
{
    SparseArray<NetworkIn> &networkInArr   = reg.get_components<NetworkIn>();
    SparseArray<Control> &controlArr       = reg.get_components<Control>();

    for (unsigned int i; i < networkInArr.size(); i++) {
        if (networkInArr[i] != std::nullopt && controlArr[i] != std::nullopt) {
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

void NetworkSystem::managePositionIn(registry &reg, Packet &packet)
{
    SparseArray<NetworkIn> &networkInArr   = reg.get_components<NetworkIn>();
    SparseArray<Position> &positionArr       = reg.get_components<Position>();

    for (unsigned int i; i < networkInArr.size(); i++) {
        if (networkInArr[i] != std::nullopt && positionArr[i] != std::nullopt) {
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
            server_->sendPacket(flag::CONTROLLER, data.Pack());
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
            server_->sendPacket(flag::POSITION, data.Pack());
        }
    }
}
