/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystem
*/

#include "NetworkSystem.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include "../ecs/ComponentsArray/Components/Components.hpp"
#include "NetworkComponent.hpp"
#include "Packet.hpp"
#include "Protocol.hpp"
#include "network_c/NetworkComponent.hpp"
#include "network_c/NetworkSystem.hpp"
#include "../../gameEngine/Game.hpp"

namespace Network {
NetworkSystem::NetworkSystem(unsigned int serverPort, std::string serverIp) : INetworkServer(serverPort)
{
}

NetworkSystem::~NetworkSystem()
{
}

void NetworkSystem::Update(registry &reg)
{
    managePlayers(reg);
    manageInputs(reg);
    manageOutputs(reg);
}

void NetworkSystem::managePlayers(registry &reg) {
    SparseArray<GameStateComponent> &gameStateArr = reg.get_components<GameStateComponent>();
    SparseArray<Spawner> &spawnerArr = reg.get_components<Spawner>();

    for (std::shared_ptr<Connection<Flag>> client : *clients_)
    {
        if (client->IsConnected() && players_.find(client->GetId()) == players_.end()) {
            Packet<Flag> addPlayerPacket;

            std::cout << "Add player " << client->GetId() << std::endl;
            addPlayerPacket.header.flag = Flag::ClientAddPlayer;
            addPlayerPacket << (uint32_t)client->GetId();
            SendToAllClients(addPlayerPacket);
            SendConnectedPlayers(client);
            players_[client->GetId()] = true;
        }
        // else if (!client->IsConnected() && players_.find(client->GetId()) != players_.end()) {
        //     Packet<Flag> removePlayerPacket;
        //     std::cout << "Remove player " << client->GetId() << std::endl;
        //     removePlayerPacket.header.flag = Flag::ClientRemovePlayer;
        //     removePlayerPacket << (uint32_t)client->GetId();
        //     SendToAllClients(removePlayerPacket);
        //     players_.erase(client->GetId());
        // }
    }
    for (size_t i = 0; i < reg._entity_number; i++)
    {
        if (gameStateArr[i].has_value())
        {
            if (gameStateArr[i]->scene == Scene::GAME)
            {
                if (clients_->size() == 0)
                {
                    std::cout << "No player connected, end game" << std::endl;
                    gameStateArr[i]->scene = Scene::END;
                }
            }
            continue;
        }
        if (spawnerArr[i].has_value())
        {
            spawnerArr[i]->playersNbr = players_.size();
        }
    }
}

/**
 * @brief Send to the client a ClientAddPlayer packet for each connected players
 * 
 * @param client the client to send the packet
 */
void NetworkSystem::SendConnectedPlayers(std::shared_ptr<Connection<Flag>> client)
{
    for (std::pair<const unsigned int, bool> &player : players_)
    {
        Packet<Flag> addPlayerPacket;
        addPlayerPacket.header.flag = Flag::ClientAddPlayer;
        addPlayerPacket << (uint32_t)player.first;
        SendToClient(addPlayerPacket, client);
    }
}

void NetworkSystem::OnClientDisconnect(std::shared_ptr<Connection<Flag>> client)
{
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
    case Flag::ServerStartGame: manageServerStartGame(reg, client, packet); break;

    default: break;
    }
}

void NetworkSystem::manageServerUpdateControls(
    registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet)
{
    SparseArray<NetworkComponent> &network = reg.get_components<NetworkComponent>();
    SparseArray<Control> &controls = reg.get_components<Control>();

    for (unsigned int i = 0; i < network.size(); i++) {
        if (network[i]->clientId == client->GetId() && controls[i].has_value()) {
            bool up, down, left, right, shoot;

            packet >> shoot >> right >> left >> down >> up;
            controls[i]->up = up;
            controls[i]->down = down;
            controls[i]->left = left;
            controls[i]->right = right;
            controls[i]->shoot = shoot;
            std::cout << "Update controls from client " << client->GetId() << " : " << up << down << left << right << shoot << std::endl;
        }
    }
}

void NetworkSystem::manageServerStartGame(registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet)
{
    SparseArray<GameStateComponent> &gameStateArr = reg.get_components<GameStateComponent>();
    SparseArray<GameLauncher> &gameLauncherArray = reg.get_components<GameLauncher>();
    size_t gameLauncherIndex = 0;

    std::cout << "Start game from client " << client->GetId() << std::endl;
    for (gameLauncherIndex = 0; gameLauncherIndex < reg._entity_number; gameLauncherIndex++) {
        if (gameLauncherArray[gameLauncherIndex].has_value())
            break;
    }
    if (!gameLauncherArray[gameLauncherIndex].has_value())
        throw std::runtime_error("No game launcher component found");
    GameLauncher &gameLauncher = *gameLauncherArray[gameLauncherIndex];

    if (gameLauncher.isGameLaunched)
        return;
    for (size_t i = 0; i < reg._entity_number; i++)
    {
        if (gameStateArr[i].has_value())
        {
            gameLauncher.isGameLaunched = true;
            // gameStateArr[i]->scene = Scene::GAME;
            packet >> gameStateArr[i]->mode;

            Packet<Flag> sendPacket;
            sendPacket.header.flag = Flag::ClientStartGame;
            sendPacket << gameStateArr[i]->mode;
            SendToAllClients(sendPacket);
        }
    }

}

void NetworkSystem::manageOutputs(registry &reg)
{
    manageClientUpdateEntity(reg);
    manageClientCreateEntity(reg);
    manageClientStartGame(reg);
    manageClientEndGame(reg);
    // debugSpaceshipPosition(reg);
}

void NetworkSystem::manageClientAddPlayer(registry &reg)
{
}

void NetworkSystem::manageClientRemovePlayer(registry &reg)
{
}

void NetworkSystem::manageClientCreateEntity(registry &reg)
{
    SparseArray<NetworkComponent> &network = reg.get_components<NetworkComponent>();
    SparseArray<Position> &position = reg.get_components<Position>();
    SparseArray<Spawner> &spawnerArr = reg.get_components<Spawner>();
    size_t spawnerIndex = 0;

    for (spawnerIndex = 0; spawnerIndex < reg._entity_number; spawnerIndex++) {
        if (spawnerArr[spawnerIndex].has_value())
            break;
    }
    if (!spawnerArr[spawnerIndex].has_value())
        throw std::runtime_error("No network info component found");
    while (spawnerArr[spawnerIndex]->entitiesToSpawn.empty() == false) {
        EntitySpawnDescriptor entity = spawnerArr[spawnerIndex]->entitiesToSpawn.front();
        Packet<Flag> packet;

        entity.entityId = ++lastEntityId_;
        packet.header.flag = Flag::ClientCreateEntity;
        packet << (uint32_t)entity.entityId;
        packet << (uint32_t)entity.clientId;
        packet << (uint32_t)entity.entityType;
        packet << (uint32_t)entity.arg1;
        packet << (uint32_t)entity.arg2;
        packet << (float)entity.x;
        packet << (float)entity.y;
        std::cout << "create : id " << entity.entityId << " type " << entity.entityType << " arg1 " << entity.arg1 << " arg2 " << entity.arg2 << std::endl;
        SendToAllClients(packet);
        spawnerArr[spawnerIndex]->spawningEntities.push(entity);
        spawnerArr[spawnerIndex]->entitiesToSpawn.pop();
    }
}

void NetworkSystem::manageClientUpdateEntity(registry &reg)
{
    SparseArray<NetworkComponent> &network = reg.get_components<NetworkComponent>();
    SparseArray<Position> &position = reg.get_components<Position>();

    for (unsigned int i = 0; i < reg._entity_number; i++) {
        if (network[i].has_value() && position[i].has_value()) {
            if (network[i]->entityId == 0)
                continue;
            Packet<Flag> packet;
            packet.header.flag = Flag::ClientUpdateEntity;
            packet << (uint32_t)network[i]->entityId;
            packet << (float)position[i]->x;
            packet << (float)position[i]->y;
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
    SparseArray<GameStateComponent> &gameStateArr = reg.get_components<GameStateComponent>();
    SparseArray<GameLauncher> &gameLauncherArray = reg.get_components<GameLauncher>();
    size_t gameLauncherIndex = 0;

    for (gameLauncherIndex = 0; gameLauncherIndex < reg._entity_number; gameLauncherIndex++) {
        if (gameLauncherArray[gameLauncherIndex].has_value())
            break;
    }
    if (!gameLauncherArray[gameLauncherIndex].has_value())
        throw std::runtime_error("No game launcher component found");
    GameLauncher &gameLauncher = *gameLauncherArray[gameLauncherIndex];

    if (!gameLauncher.isGameLaunched)
        return;
    for (size_t i = 0; i < reg._entity_number; i++)
    {
        if (gameStateArr[i].has_value())
        {
            if (gameStateArr[i]->scene == Scene::END)
            {
                std::cout << "End game" << std::endl;
                Packet<Flag> packet;
                packet.header.flag = Flag::ClientEndGame;
                SendToAllClients(packet);
                gameLauncher.isGameLaunched = false;
            }
            return;
        }
    }
}

void NetworkSystem::debugSpaceshipPosition(registry &reg)
{
    SparseArray<NetworkComponent> &network = reg.get_components<NetworkComponent>();
    SparseArray<Position> &position = reg.get_components<Position>();
    SparseArray<Tag> &tag = reg.get_components<Tag>();

    for (unsigned int i = 0; i < network.size(); i++) {
        if (position[i].has_value() && (tag[i].has_value() &&  tag[i]->tag == "starship")) {
            // if (network[i]->entityId == 0)
            //     continue;
            // std::cout << "Spaceship " << network[i]->entityId << " : " << position[i]->x << " " << position[i]->y << std::endl;
            std::cout << "Spaceship pos : " << position[i]->x << " " << position[i]->y << std::endl;
        }
    }
}

};  // namespace Network
