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
#include "NetworkS.hpp"

namespace Network {

class UdpServer;

class NetworkSystem// : public INetworkServer<Flag>
{
public:
    NetworkSystem(unsigned int serverPort);
    ~NetworkSystem();

    void Update(registry &reg);
    void setNetwork(NetworkS *ptrNetworkS);
    void send_system(registry &r);

private:
    void manageInputs(registry &reg);
    // void managePacketIn(registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag>& msg);

    // void manageServerGetPing(std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet);
    // void manageServerConnect(std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet);
    // void manageServerUpdateControls(registry &reg, std::shared_ptr<Connection<Flag>> client, Packet<Flag> &packet);

    void manageOutputs(registry &reg);

    NetworkS *_ptrNetworkS;


};

};  // namespace Network

#endif /* !NETWORKSYSTEM_HPP_ */
