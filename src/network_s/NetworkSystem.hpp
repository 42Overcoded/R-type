/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystem
*/

#ifndef NETWORKSYSTEM_HPP_
#define NETWORKSYSTEM_HPP_
#include "../ecs/ComponentsArray/Systems/SfmlSystem.hpp"
#include "Network.hpp"
#include <string>
#include <memory>

class NetworkSystem : SfmlSystem
{
public:
    NetworkSystem(unsigned int serverPort);
    ~NetworkSystem();

    void update(registry &reg);
protected:
private:
    std::unique_ptr<UdpServer> server_;
};

#endif /* !NETWORKSYSTEM_HPP_ */
