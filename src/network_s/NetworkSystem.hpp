/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystem
*/

#ifndef NETWORKSYSTEM_HPP_
#define NETWORKSYSTEM_HPP_
#include <string>
#include <memory>

class UdpServer;
class Packet;
class registry;

class NetworkSystem
{
public:
    NetworkSystem(unsigned int serverPort);
    ~NetworkSystem();

    void update(registry &reg);
private:
    void manageConnectIn(registry &reg, Packet &packet, std::string client);
    void manageDisconnectIn(registry &reg, Packet &packet, std::string client);
    void manageControllerIn(registry &reg, Packet &packet, std::string client);
    void managePositionIn(registry &reg, Packet &packet, std::string client);
    void manageControllerOut(registry &reg);
    void managePositionOut(registry &reg);
    void manageInputs(registry &reg);
    void manageOutputs(registry &reg);
private:
    std::unique_ptr<UdpServer> server_;
};

#endif /* !NETWORKSYSTEM_HPP_ */
