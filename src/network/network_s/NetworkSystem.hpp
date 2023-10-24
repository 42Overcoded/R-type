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
#include "../Protocol.hpp"
#include "../ecs/Registry.hpp"

namespace Network {

class UdpServer;

class NetworkSystem : public INetworkServer<Flag>
{
public:
    NetworkSystem(unsigned int serverPort, std::string serverIp);
    ~NetworkSystem();

    void Update(registry &reg);

private:
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
private:
};

};  // namespace Network

#endif /* !NETWORKSYSTEM_HPP_ */
