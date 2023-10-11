/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkComponent
*/

#ifndef NETWORKCOMPONENT_HPP_
#define NETWORKCOMPONENT_HPP_
#include "Network.hpp"
#include <memory>

struct NetworkIn
{
    std::shared_ptr<ITransmission> transmission;
};

struct NetworkOut
{
    std::shared_ptr<ITransmission> transmission;
};

#endif /* !NETWORKCOMPONENT_HPP_ */
