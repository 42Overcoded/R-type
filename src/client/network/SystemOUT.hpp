/*
** EPITECH PROJECT, 2023
** src
** File description:
** SystemOUT
*/

#ifndef SYSTEMOUT_HPP_
#define SYSTEMOUT_HPP_

#include "../ecs/Registry.hpp"

class SystemOUT {
    public:
        SystemOUT();
        ~SystemOUT();
        void update(registry &r);

    protected:
    private:
};

#endif /* !SYSTEMOUT_HPP_ */
