/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkSystems
*/

#include "NetworkSystems.hpp"

void NetworkSystem::setNetwork(Network *ptrNetwork)
{
    _ptrNetwork = ptrNetwork;
}


void NetworkSystem::send_system(registry &r)
{
    SparseArray<ComponentOUT> &SpAr = r.get_components<ComponentOUT>();

    for (int i = 0; i < SpAr.size(); i++) {
        if (SpAr[i] != std::nullopt && _ptrNetwork != NULL) {
            _ptrNetwork->send_info_to_client(SpAr[i]->ptrToThisStruct);
        }
    }
}
