/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystem
*/

#ifndef CLIENTNETWORKSYSTEM_HPP_
#define CLIENTNETWORKSYSTEM_HPP_
#include <cstdint>
#include <memory>
#include <string>
#include "../ecs/Registry.hpp"
#include "../Protocol.hpp"
#include "../INetworkClient.hpp"
#include "../INetworkSystem.hpp"

namespace Network {
class ClientNetworkSystem: public INetworkClient<Flag>, public INetworkSystem
{
public:
    ClientNetworkSystem(unsigned int serverPort, std::string &serverIp);
    ~ClientNetworkSystem();

    void Update(registry &reg);

private:
    // Inputs
    void managePlayerNbr(registry &reg);
    void manageInputs(registry &reg);
    void managePacketIn(registry &reg, Packet<Flag> &packet);

    void manageClientAccepted(registry &reg, Packet<Flag> &packet);
    void manageClientDenied(registry &reg, Packet<Flag> &packet);
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
    std::uint32_t clientId_ = 0;
    std::uint32_t playersNbr_ = 0;
};
};  // namespace Nerwork

#endif /* !CLIENTNETWORKSYSTEM_HPP_ */
