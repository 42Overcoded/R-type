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
            switch (packet.header.flag)
            {
            case Flag::Client_Accepted: manageClientAccepted(reg, packet); break;
            case Flag::Client_AssignID: manageClientAssignID(reg, packet); break;
            case Flag::Client_RegisterWithServer: manageRegisterWithServer(reg, packet); break;
            case Flag::Client_UnregisterWithServer: manageUnregisterWithServer(reg, packet); break;
            case Flag::Game_AddPlayer: manageAddPlayer(reg, packet); break;
            case Flag::Game_RemovePlayer: manageRemovePlayer(reg, packet); break;
            case Flag::Game_UpdatePlayer: manageUpdatePlayer(reg, packet); break;
            default: break;
            }
        }
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

void NetworkSystem::manageRegisterWithServer(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkIn> &networkInArr = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageUnregisterWithServer(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkIn> &networkInArr = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageAddPlayer(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkIn> &networkInArr = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageRemovePlayer(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkIn> &networkInArr = reg.get_components<NetworkIn>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageUpdatePlayer(registry &reg, Packet<Flag> &packet)
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
