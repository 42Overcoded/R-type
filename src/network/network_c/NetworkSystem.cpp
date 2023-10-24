/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystem
*/

#include "NetworkSystem.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include "../Protocol.hpp"
#include "../ecs/ComponentsArray/Components/Components.hpp"
#include "NetworkComponent.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"

namespace Network {
NetworkSystem::NetworkSystem(unsigned int serverPort, std::string serverIp) : INetworkClient()
{
    try
    {
        Connect(serverIp, serverPort);
    }
    catch (std::exception &e)
    {
        std::cout << "Can't use server Port : " << serverPort << std::endl;
    }
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
    if (IsConnected())
    {
        if (!Incoming().IsEmpty())
        {
            Packet packet = Incoming().PopFront().packet;
            managePacketIn(reg, packet);
        }
    }
}

void NetworkSystem::managePacketIn(registry &reg, Packet<Flag> &packet)
{
    switch (packet.header.flag)
    {
    case Flag::ClientAccepted: manageClientAccepted(reg, packet); break;
    case Flag::ClientAssignID: manageClientAssignID(reg, packet); break;
    case Flag::ClientSendPing: manageClientSendPing(reg, packet); break;
    case Flag::ClientAddPlayer: manageClientAddPlayer(reg, packet); break;
    case Flag::ClientRemovePlayer: manageClientRemovePlayer(reg, packet); break;
    case Flag::ClientCreateEntity: manageClientCreateEntity(reg, packet); break;
    case Flag::ClientUpdateEntity: manageClientUpdateEntity(reg, packet); break;
    default: break;
    }
}

void NetworkSystem::manageClientAccepted(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client accepted" << std::endl;
}

void NetworkSystem::manageClientAssignID(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkComponent> &networkInArr = reg.get_components<NetworkComponent>();
    SparseArray<Control> &controllArr = reg.get_components<Control>();

    std::cout << "Client assign ID" << std::endl;
    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt && controllArr[i] != std::nullopt)
        {
            packet >> networkInArr[i]->clientId;
        }
    }
}

void NetworkSystem::manageClientSendPing(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client send ping" << std::endl;
    SparseArray<NetworkComponent> &networkInArr = reg.get_components<NetworkComponent>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientAddPlayer(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client add player" << std::endl;
    SparseArray<NetworkComponent> &networkInArr = reg.get_components<NetworkComponent>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientRemovePlayer(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client remove player" << std::endl;
    SparseArray<NetworkComponent> &networkInArr = reg.get_components<NetworkComponent>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientCreateEntity(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client create entity" << std::endl;
    
}

void NetworkSystem::manageClientUpdateEntity(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client update entity" << std::endl;
    SparseArray<NetworkComponent> &networkInArr = reg.get_components<NetworkComponent>();
    SparseArray<Position> &positionArr = reg.get_components<Position>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt && positionArr[i] != std::nullopt)
        {
            uint32_t entityId;

            packet >> entityId;
            if (networkInArr[i]->entityId != 0 && networkInArr[i]->entityId == entityId) {
                uint32_t x;
                uint32_t y;

                packet >> x >> y;
                positionArr[i]->x = x;
                positionArr[i]->y = y;
            }
        }
    }
}

void NetworkSystem::manageClientDestroyEntity(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client destroy entity" << std::endl;
    SparseArray<NetworkComponent> &networkInArr = reg.get_components<NetworkComponent>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientStartGame(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client start game" << std::endl;
    SparseArray<NetworkComponent> &networkInArr = reg.get_components<NetworkComponent>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientEndGame(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client end game" << std::endl;
    SparseArray<NetworkComponent> &networkInArr = reg.get_components<NetworkComponent>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageOutputs(registry &reg)
{
    if (IsConnected())
    {
        // manageServerGetPing();
        manageServerUpdateControls(reg);
    }
}

void NetworkSystem::manageServerGetPing(void)
{
    Packet<Flag> packet;

    std::cout << "Send ping to server" << std::endl;
    packet.header.flag = Flag::ServerGetPing;
    SendToServer(packet);
}

void NetworkSystem::manageServerUpdateControls(registry &reg)
{
    SparseArray<NetworkComponent> &networkInArr = reg.get_components<NetworkComponent>();
    SparseArray<Control> &controllArr = reg.get_components<Control>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt && controllArr[i] != std::nullopt)
        {
            std::cout << "Send controls to server" << std::endl;
            Packet<Flag> packet;
            packet.header.flag = Flag::ServerUpdateControls;
            packet << controllArr[i]->up << controllArr[i]->down << controllArr[i]->left << controllArr[i]->right << controllArr[i]->shoot;
            SendToServer(packet);
        }
    }
}

void NetworkSystem::manageServerStartGame(registry &reg)
{
    Packet<Flag> packet;

    std::cout << "Send start game to server" << std::endl;
    packet.header.flag = Flag::ServerStartGame;
    SendToServer(packet);
}

}  // namespace Network
