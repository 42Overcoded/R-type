/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkComponent
*/

#ifndef NETWORKCOMPONENT_HPP_
#define NETWORKCOMPONENT_HPP_
#include "Network.hpp"

struct NetworkIn
{
    std::unique_ptr<ITransmission> transmission;
};

struct NetworkOut
{
    std::unique_ptr<ITransmission> transmission;
};

#endif /* !NETWORKCOMPONENT_HPP_ */
