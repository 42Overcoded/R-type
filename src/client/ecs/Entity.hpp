/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <cstddef>
#include "SparseArray.hpp"

class entity_t {
public:
    explicit entity_t(std::size_t value) : value_(value) {}   

    operator std::size_t() const {
        return value_;
    }
    private:
        std::size_t value_;
};

#endif /* !ENTITY_HPP_ */
