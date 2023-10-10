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
    std::array<boost::asio::mutable_buffer, 3> buffer;
};

struct NetworkOut
{
    std::array<boost::asio::mutable_buffer, 3> buffer;
};

#endif /* !NETWORKCOMPONENT_HPP_ */
