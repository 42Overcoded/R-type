/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystem
*/

#include "NetworkSystem.hpp"
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include "../ecs/ComponentsArray/Components/Components.hpp"
#include "NetworkComponent.hpp"
#include "network_c/NetworkSystem.hpp"

namespace Network {
NetworkSystem::NetworkSystem(unsigned int serverPort, std::string serverIp) : INetworkServer(serverPort)
{
}

NetworkSystem::~NetworkSystem()
{
}

void NetworkSystem::Update(registry &reg)
{
    manageInputs(reg);
    manageOutputs(reg);
}


void NetworkSystem::manageInputs(registry &reg)
{
    size_t nMessageCount = 0;

    while (nMessageCount < MaxPacketsProcessed && !packetsInQueue_.IsEmpty())
    {
        auto packet = packetsInQueue_.PopFront();
        managePacketIn(reg, packet.remote, packet.packet);
        nMessageCount++;
    }
}

void NetworkSystem::managePacketIn(
    registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet)
{
    switch (packet.header.flag)
    {
    case Flag::ServerUpdateControls: manageServerUpdateControls(reg, client, packet); break;
    default: break;
    }
}

void NetworkSystem::manageServerUpdateControls(
    registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet)
{
    auto &network = reg.get_components<NetworkComponent>();
    auto &controls = reg.get_components<Control>();

    std::cout << "Update controls from client " << client->GetId() << std::endl;
    for (unsigned int i = 0; i < network.size(); i++) {
        if (network[i]->clientId == client->GetId() && controls[i] != std::nullopt) {
            packet >> controls[i]->up >> controls[i]->down >> controls[i]->left >> controls[i]->right;
        }
    }
}

void NetworkSystem::manageServerStartGame(registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet)
{
}

void NetworkSystem::manageOutputs(registry &reg)
{
    manageClientUpdateEntity(reg);
    manageClientCreateEntity(reg);
}

void NetworkSystem::manageClientAddPlayer(registry &reg)
{
}

void NetworkSystem::manageClientRemovePlayer(registry &reg)
{
}

void NetworkSystem::manageClientCreateEntity(registry &reg)
{
    auto &network = reg.get_components<NetworkComponent>();
    auto &position = reg.get_components<Position>();

    for (unsigned int i = 0; i < network.size(); i++) {
        if (network[i] != std::nullopt && position[i] != std::nullopt) {
            std::cout << "create : id " << network[i]->entityId << " pos " << position[i]->x << " " << position[i]->y << std::endl;
            if (network[i]->entityId != 0)
                continue;
            network[i]->entityId = ++lastEntityId_;
            Packet<Flag> packet;
            packet.header.flag = Flag::ClientCreateEntity;
            packet << (uint32_t)network[i]->entityId << (uint32_t)position[i]->x << (uint32_t)position[i]->y;
            std::cout << "create : id " << network[i]->entityId << " pos " << position[i]->x << " " << position[i]->y << std::endl;
            SendToAllClients(packet);
        }
    }
}

void NetworkSystem::manageClientUpdateEntity(registry &reg)
{
    auto &network = reg.get_components<NetworkComponent>();
    auto &position = reg.get_components<Position>();

    for (unsigned int i = 0; i < network.size(); i++) {
        if (network[i] != std::nullopt && position[i] != std::nullopt) {
            if (network[i]->entityId == 0)
                continue;
            Packet<Flag> packet;
            packet.header.flag = Flag::ClientUpdateEntity;
            packet << (uint32_t)network[i]->entityId << (uint32_t)position[i]->x << (uint32_t)position[i]->y;
            std::cout << "update : id " << network[i]->entityId << " pos " << position[i]->x << " " << position[i]->y << std::endl;
            SendToAllClients(packet);
        }
    }
}

void NetworkSystem::manageClientDestroyEntity(registry &reg)
{
}

void NetworkSystem::manageClientStartGame(registry &reg)
{
}

void NetworkSystem::manageClientEndGame(registry &reg)
{
}

};  // namespace Network
