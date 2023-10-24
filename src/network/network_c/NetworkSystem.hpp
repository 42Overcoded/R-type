/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystem
*/

#ifndef NETWORKSYSTEM_HPP_
#define NETWORKSYSTEM_HPP_
#include <cstdint>
#include <memory>
#include <string>
#include "../ecs/Registry.hpp"
#include "../Protocol.hpp"
#include "../INetworkClient.hpp"

namespace Network {
class NetworkSystem: public INetworkClient<Flag>
{
public:
    NetworkSystem(unsigned int serverPort, std::string serverIp);
    ~NetworkSystem();

    void Update(registry &reg);

private:
    // Inputs
    void manageInputs(registry &reg);
    void managePacketIn(registry &reg, Packet<Flag> &packet);

    void manageClientAccepted(registry &reg, Packet<Flag> &packet);
    void manageClientAssignID(registry &reg, Packet<Flag> &packet);
    void manageClientSendPing(registry &reg, Packet<Flag> &packet);
    void manageClientAddPlayer(registry &reg, Packet<Flag> &packet);
    void manageClientRemovePlayer(registry &reg, Packet<Flag> &packet);
    void manageClientCreateEntity(registry &reg, Packet<Flag> &packet);
    void manageClientUpdateEntity(registry &reg, Packet<Flag> &packet);
    void manageClientDestroyEntity(registry &reg, Packet<Flag> &packet);
    void manageClientStartGame(registry &reg, Packet<Flag> &packet);
    void manageClientEndGame(registry &reg, Packet<Flag> &packet);

    // Outputs
    void manageOutputs(registry &reg);

    void manageServerGetPing(void);
    void manageServerConnect(void);
    void manageServerUpdateControls(registry &reg);
    void manageServerStartGame(registry &reg);

private:
    std::uint32_t clientId_;
};
};  // namespace Nerwork

#endif /* !NETWORKSYSTEM_HPP_ */
