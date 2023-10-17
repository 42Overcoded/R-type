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

namespace Network {
NetworkSystem::NetworkSystem(unsigned int serverPort)// : INetworkServer(serverPort)
{
    _ptrNetworkS = NULL;
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

    // while (nMessageCount < MaxPacketsProcessed && !packetsInQueue_.IsEmpty())
    // {
    //     auto packet = packetsInQueue_.PopFront();
    //     managePacketIn(reg, packet.remote, packet.packet);
    //     nMessageCount++;
    // }
}

// void NetworkSystem::managePacketIn(
//     registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet)
// {
//     switch (packet.header.flag)
//     {
//     case Flag::ServerUpdateControls: manageServerUpdateControls(reg, client, packet); break;
//     default: break;
//     }
// }

// void NetworkSystem::manageServerUpdateControls(
//     registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet)
// {
//     auto &network = reg.get_components<NetworkComponent>();
//     auto &controls = reg.get_components<Control>();

//     std::cout << "Update controls from client " << client->GetId() << std::endl;
//     for (unsigned int i = 0; i < network.size(); i++) {
//         if (network[i]->clientId == client->GetId() && controls[i] != std::nullopt) {
//             packet >> controls[i];
//         }
//     }
// }

void NetworkSystem::manageOutputs(registry &reg)
{
    //TODO: manageOutputs
}

void NetworkSystem::setNetwork(NetworkS *ptrNetworkS)
{
    _ptrNetworkS = ptrNetworkS;
}


void NetworkSystem::send_system(registry &r)
{
    SparseArray<ComponentOUT> &SpAr = r.get_components<ComponentOUT>();

    for (int i = 0; i < SpAr.size(); i++) {
        if (SpAr[i] != std::nullopt && _ptrNetworkS != NULL) {
            _ptrNetworkS->send_info_to_client(SpAr[i]->ptrToThisStruct);
        }
    }
}

};  // namespace Network
