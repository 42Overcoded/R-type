/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** INetworkSystem
*/

#ifndef INETWORKSYSTEM_HPP_
#define INETWORKSYSTEM_HPP_
#include "../ecs/Registry.hpp"

namespace Network {
    class INetworkSystem {
        public:
            virtual ~INetworkSystem() = default;
            virtual void Update(registry &reg) = 0;
    };
}

#endif /* !INETWORKSYSTEM_HPP_ */
