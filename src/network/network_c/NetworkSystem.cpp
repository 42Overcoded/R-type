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
    std::cout << "Client assign ID" << std::endl;
    SparseArray<NetworkComponent> &networkInArr = reg.get_components<NetworkComponent>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
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
    SparseArray<NetworkComponent> &networkInArr = reg.get_components<NetworkComponent>();

    for (unsigned int i; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
    }
}

void NetworkSystem::manageClientUpdateEntity(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client update entity" << std::endl;
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
        manageServerGetPing();
    }
}

void NetworkSystem::manageServerGetPing(void)
{
    Packet<Flag> packet;

    std::cout << "Send ping to server" << std::endl;
    packet.header.flag = Flag::ServerGetPing;
    SendToServer(packet);
}

void NetworkSystem::setNetwork(NetworkC *ptrNetworkC)
{
    _ptrNetworkC = ptrNetworkC;
}


void NetworkSystem::send_system(registry &r)
{
    SparseArray<ComponentOUT> &SpAr = r.get_components<ComponentOUT>();

    for (int i = 0; i < SpAr.size(); i++) {
        if (SpAr[i] != std::nullopt && _ptrNetworkC != NULL) {
            _ptrNetworkC->send_info_to_server(SpAr[i]->ptrToThisStruct);
        }
    }
}

}  // namespace Network
