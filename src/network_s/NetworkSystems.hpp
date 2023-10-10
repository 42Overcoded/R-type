/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystems
*/

#ifndef NETWORKSYSTEMS_HPP_
#define NETWORKSYSTEMS_HPP_
#include "../ecs/Registry.hpp"
#include "Network.hpp"
#include "NetworkComponents.hpp"

class NetworkSystem {
    public:
        NetworkSystem() = default;
        ~NetworkSystem() = default;

        void send_system(registry &r);
        void setNetwork(Network *ptrNetwork);
    protected:
    private:
        Network *_ptrNetwork = NULL;
};

#endif /* !NETWORKSYSTEMS_HPP_ */
