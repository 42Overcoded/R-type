/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystem
*/

#ifndef NETWORKSYSTEM_HPP_
#define NETWORKSYSTEM_HPP_
#include <memory>
#include <string>
#include "../INetworkServer.hpp"
#include "../INetworkSystem.hpp"
#include "../Protocol.hpp"
#include "../ecs/Registry.hpp"
#include <unordered_map>

namespace Network {

class ServerNetworkSystem : public INetworkServer<Flag>, public INetworkSystem
{
public:
    ServerNetworkSystem(unsigned int serverPort, std::string &serverIp);
    ~ServerNetworkSystem();

    void Update(registry &reg);

private:
    void managePlayers(registry &reg);
    void SendConnectedPlayers(std::shared_ptr<Connection<Flag>> client);

    void manageInputs(registry &reg);
    void managePacketIn(registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag>& msg);

    void manageServerUpdateControls(registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet);
    void manageServerStartGame(registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet);

    void manageOutputs(registry &reg);

    void manageClientAddPlayer(registry &reg);
    void manageClientRemovePlayer(registry &reg);
    void manageClientCreateEntity(registry &reg);
    void manageClientUpdateEntity(registry &reg);
    void manageClientDestroyEntity(registry &reg);
    void manageClientStartGame(registry &reg);
    void manageClientEndGame(registry &reg);

    void debugSpaceshipPosition(registry &reg);
    void OnClientDisconnect(std::shared_ptr<Connection<Flag>> client) override;
private:
    std::unordered_map<unsigned int, bool> players_;
    std::vector<unsigned int> assignedClientIds_;
};

};  // namespace Network

#endif /* !NETWORKSYSTEM_HPP_ */
