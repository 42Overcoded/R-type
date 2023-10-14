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
    void manageClientAccepted(registry &reg, Packet<Flag> &packet);
    void manageClientAssignID(registry &reg, Packet<Flag> &packet);
    void manageRegisterWithServer(registry &reg, Packet<Flag> &packet);
    void manageUnregisterWithServer(registry &reg, Packet<Flag> &packet);
    void manageAddPlayer(registry &reg, Packet<Flag> &packet);
    void manageRemovePlayer(registry &reg, Packet<Flag> &packet);
    void manageUpdatePlayer(registry &reg, Packet<Flag> &packet);



private:
    std::uint32_t clientId_;
};
};  // namespace Nerwork

#endif /* !NETWORKSYSTEM_HPP_ */
