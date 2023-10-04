/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystem
*/

#include <memory>
#include <optional>
#include <iostream>
#include <string>
#include "NetworkSystem.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"

NetworkSystem::NetworkSystem(int serverPort)
{
    try
    {
        server_ = std::make_unique<UdpServer>(serverPort);
    } catch (std::exception &e) {
        std::cout << "Can't user server Port : " << serverPort << std::endl;
    }
}

NetworkSystem::~NetworkSystem()
{
}

void NetworkSystem::update(registry &reg)
{
    SparseArray<NetworkIn> networkInArr   = reg.get_components<NetworkIn>();
    SparseArray<NetworkOut> networkOutArr = reg.get_components<NetworkOut>();

    for (int i = 0; i < networkInArr.size(); i++)
    {
        if (networkInArr[i] != std::nullopt)
        {
        }
        if (networkOutArr[i] != std::nullopt)
        {
        }
    }
}
