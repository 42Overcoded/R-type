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
#include "../../../gameEngine/Game.hpp"
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
    managePlayerNbr(reg);
    manageInputs(reg);
    manageOutputs(reg);
}

void NetworkSystem::managePlayerNbr(registry &reg)
{
    SparseArray<GameStateComponent> &gameStateArr = reg.get_components<GameStateComponent>();
    SparseArray<Tag> &tagArr                      = reg.get_components<Tag>();
    SparseArray<Text> &textArr                    = reg.get_components<Text>();
    SparseArray<NetworkInfo> &networkInfoArr      = reg.get_components<NetworkInfo>();

    for (size_t i = 0; i < reg._entity_number; i++)
    {
        if (gameStateArr[i].has_value())
        {
            if (gameStateArr[i]->scene != ONLINE)
            {
                return;
            }
            break;
        }
    }
    for (size_t i = 0; i < reg._entity_number; i++)
    {
        if (tagArr[i].has_value())
        {
            if (tagArr[i]->tag == "playerConnected" && textArr[i].has_value())
            {
                std::string str = std::to_string(playersNbr_) + " / 4 Players connected";
                textArr[i]->str = str;
            }
        }
        if (networkInfoArr[i].has_value())
        {
            networkInfoArr[i]->playersNbr = playersNbr_;
        }
    }
}

void NetworkSystem::manageInputs(registry &reg)
{
    if (IsConnected())
    {
        for (int count = 0; !Incoming().IsEmpty() && count < 10; count++)
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
    case Flag::ClientDenied: manageClientDenied(reg, packet); break;
    case Flag::ClientAssignID: manageClientAssignID(reg, packet); break;
    case Flag::ClientSendPing: manageClientSendPing(reg, packet); break;
    case Flag::ClientAddPlayer: manageClientAddPlayer(reg, packet); break;
    case Flag::ClientRemovePlayer: manageClientRemovePlayer(reg, packet); break;
    case Flag::ClientCreateEntity: manageClientCreateEntity(reg, packet); break;
    case Flag::ClientUpdateEntity: manageClientUpdateEntity(reg, packet); break;
    case Flag::ClientDestroyEntity: manageClientDestroyEntity(reg, packet); break;
    case Flag::ClientStartGame: manageClientStartGame(reg, packet); break;
    case Flag::ClientEndGame: manageClientEndGame(reg, packet); break;
    default: break;
    }
}

void NetworkSystem::manageClientAccepted(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client accepted" << std::endl;
}

void NetworkSystem::manageClientDenied(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client denied" << std::endl;
}

void NetworkSystem::manageClientAssignID(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkComponent> &networkArr     = reg.get_components<NetworkComponent>();
    SparseArray<GameStateComponent> &gameStateArr = reg.get_components<GameStateComponent>();

    std::cout << "Client assign ID" << std::endl;
    for (size_t i = 0; i < reg._entity_number; i++)
    {
        if (networkArr[i].has_value() && gameStateArr[i].has_value())
        {
            uint32_t clientId;

            packet >> clientId;
            networkArr[i]->clientId = clientId;
            std::cout << "assign : id " << networkArr[i]->clientId << std::endl;
        }
    }
}

void NetworkSystem::manageClientSendPing(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client send ping" << std::endl;
    SparseArray<NetworkComponent> &networkArr = reg.get_components<NetworkComponent>();

    for (size_t i = 0; i < networkArr.size(); i++)
    {
        if (networkArr[i].has_value())
        {
        }
    }
}

void NetworkSystem::manageClientAddPlayer(registry &reg, Packet<Flag> &packet)
{
    uint32_t clientId;

    packet >> clientId;
    std::cout << "Client add player : " << clientId << std::endl;
    playersNbr_++;
}

void NetworkSystem::manageClientRemovePlayer(registry &reg, Packet<Flag> &packet)
{
    uint32_t clientId;

    packet >> clientId;
    std::cout << "Client remove player : " << clientId << std::endl;
    playersNbr_--;
}

void NetworkSystem::manageClientCreateEntity(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkComponent> &networkArr = reg.get_components<NetworkComponent>();
    SparseArray<Position> &positionArr        = reg.get_components<Position>();
    uint32_t entityId;
    float x;
    float y;

    packet >> y;
    packet >> x;
    packet >> entityId;

    std::cout << "client create entity : " << entityId << " " << x << " " << y << std::endl;
    for (size_t i = 0; i < networkArr.size(); i++)
    {
        if (networkArr[i].has_value() && positionArr[i].has_value())
        {
            //TODO replace with true creator code
            if (networkArr[i]->entityId != 0)
                continue;
            networkArr[i]->entityId = entityId;
            std::cout << "create : id " << networkArr[i]->entityId << std::endl;
            return;
        }
    }
}

void NetworkSystem::manageClientUpdateEntity(registry &reg, Packet<Flag> &packet)
{
    SparseArray<NetworkComponent> &networkArr = reg.get_components<NetworkComponent>();
    SparseArray<Position> &positionArr        = reg.get_components<Position>();
    uint32_t entityId;
    float x;
    float y;

    packet >> y;
    packet >> x;
    packet >> entityId;

    std::cout << "Client update entity : " << entityId << " " << x << " " << y << std::endl;
    for (size_t i = 0; i < reg._entity_number; i++)
    {
        if (networkArr[i].has_value() && positionArr[i].has_value())
        {
            if (networkArr[i]->entityId != 0 && networkArr[i]->entityId == entityId)
            {
                positionArr[i]->x = x;
                positionArr[i]->y = y;
                std::cout << "update entity : " << networkArr[i]->entityId << " " << positionArr[i]->x << " " << positionArr[i]->y << std::endl;
                return;
            }
        }
    }
    std::cout << "Client update entity : not found" << std::endl;
}

void NetworkSystem::manageClientDestroyEntity(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client destroy entity" << std::endl;
    SparseArray<NetworkComponent> &networkArr = reg.get_components<NetworkComponent>();

    for (size_t i = 0; i < networkArr.size(); i++)
    {
        if (networkArr[i].has_value())
        {
        }
    }
}

void NetworkSystem::manageClientStartGame(registry &reg, Packet<Flag> &packet)
{
    std::cout << "Client start game" << std::endl;
    SparseArray<GameStateComponent> &gameStateArr = reg.get_components<GameStateComponent>();
    auto &gameLauncherArray                       = reg.get_components<GameLauncher>();
    size_t gameLauncherIndex                      = 0;

    for (gameLauncherIndex = 0; gameLauncherIndex < reg._entity_number; gameLauncherIndex++)
    {
        if (gameLauncherArray[gameLauncherIndex].has_value())
            break;
    }
    if (!gameLauncherArray[gameLauncherIndex].has_value())
        throw std::runtime_error("No game launcher component found");
    GameLauncher &gameLauncher = *gameLauncherArray[gameLauncherIndex];

    for (size_t i = 0; i < reg._entity_number; i++)
    {
        if (gameStateArr[i].has_value())
        {
            packet >> gameStateArr[i]->mode;
            gameLauncher.isGameLaunched = true;
        }
    }
}

void NetworkSystem::manageClientEndGame(registry &reg, Packet<Flag> &packet)
{
    std::cout << "receive end game" << std::endl;
    SparseArray<GameStateComponent> &gameStateArr = reg.get_components<GameStateComponent>();

    for (size_t i = 0; i < reg._entity_number; i++)
    {
        if (gameStateArr[i].has_value())
        {
            gameStateArr[i]->scene = Scene::END;
            return;
        }
    }
}

void NetworkSystem::manageOutputs(registry &reg)
{
    if (IsConnected())
    {
        // manageServerGetPing();
        manageServerUpdateControls(reg);
        manageServerStartGame(reg);
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
    SparseArray<NetworkComponent> &networkArr = reg.get_components<NetworkComponent>();
    SparseArray<Control> &controllArr         = reg.get_components<Control>();

    for (size_t i = 0; i < networkArr.size(); i++)
    {
        if (networkArr[i].has_value() && controllArr[i].has_value())
        {
            Packet<Flag> packet;
            packet.header.flag = Flag::ServerUpdateControls;
            packet << controllArr[i]->up;
            packet << controllArr[i]->down;
            packet << controllArr[i]->left;
            packet << controllArr[i]->right;
            packet << controllArr[i]->shoot;
            std::cout << "Send controls to server : " << controllArr[i]->up << controllArr[i]->down
                      << controllArr[i]->left << controllArr[i]->right << controllArr[i]->shoot
                      << std::endl;
            SendToServer(packet);
            return;
        }
    }
}

void NetworkSystem::manageServerStartGame(registry &reg)
{
    SparseArray<GameStateComponent> &gameStateArr = reg.get_components<GameStateComponent>();
    auto &gameLauncherArray                       = reg.get_components<GameLauncher>();
    size_t gameLauncherIndex                      = 0;

    for (gameLauncherIndex = 0; gameLauncherIndex < reg._entity_number; gameLauncherIndex++)
    {
        if (gameLauncherArray[gameLauncherIndex].has_value())
            break;
    }
    if (!gameLauncherArray[gameLauncherIndex].has_value())
        throw std::runtime_error("No game launcher component found");
    GameLauncher &gameLauncher = *gameLauncherArray[gameLauncherIndex];

    if (gameLauncher.isWaitingForServer || !gameLauncher.isRequestingGame)
        return;
    for (size_t i = 0; i < reg._entity_number; i++)
    {
        if (gameStateArr[i].has_value())
        {
            if (gameStateArr[i]->scene == Scene::ONLINE)
            {
                std::cout << "Send start game to server" << std::endl;
                Packet<Flag> packet;

                packet.header.flag = Flag::ServerStartGame;
                packet << gameStateArr[i]->mode;
                SendToServer(packet);
                gameLauncher.isWaitingForServer = true;
            }
            return;
        }
    }
}

}  // namespace Network
