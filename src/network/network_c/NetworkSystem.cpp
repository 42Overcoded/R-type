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
#include "../Protocol.hpp"
#include "../ecs/ComponentsArray/Components/Components.hpp"
#include "NetworkComponent.hpp"

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
    SparseArray<NetworkIn> &networkInArr = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientAssignID(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkIn> &networkInArr = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientSendPing(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkIn> &networkInArr = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientAddPlayer(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkIn> &networkInArr = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientRemovePlayer(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkIn> &networkInArr = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientCreateEntity(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkIn> &networkInArr = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientUpdateEntity(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkIn> &networkInArr = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

}  // namespace Network
