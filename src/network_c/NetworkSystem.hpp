/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystem
*/

#ifndef NETWORKSYSTEM_HPP_
#define NETWORKSYSTEM_HPP_
#include "Network.hpp"
#include <string>
#include <memory>

class NetworkSystem
{
public:
    NetworkSystem(unsigned int serverPort, std::string serverIp);
    ~NetworkSystem();

    void update(registry &reg);
private:
    void manageConnectIn(registry &reg, Packet &packet);
    void manageDisconnectIn(registry &reg, Packet &packet);
    void manageControllerIn(registry &reg, Packet &packet);
    void managePositionIn(registry &reg, Packet &packet);
    void manageControllerOut(registry &reg);
    void managePositionOut(registry &reg);
    void manageInputs(registry &reg);
    void manageOutputs(registry &reg);
private:
    std::unique_ptr<UdpClient> server_;
};

#endif /* !NETWORKSYSTEM_HPP_ */
