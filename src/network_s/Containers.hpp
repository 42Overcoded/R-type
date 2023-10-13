/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Containers
*/

#ifndef CONTAINERS_HPP_
#define CONTAINERS_HPP_
#include <iostream>
#include <vector>

struct IContainer
{
public:
    IContainer() = default;

    virtual std::vector<unsigned char> Pack()       = 0;
    virtual void Unpack(const std::vector<unsigned char> &data) = 0;
};

struct ControllerContainer : public IContainer
{
    std::vector<unsigned char> Pack() final
    {
        std::vector<unsigned char> packedData;
        packedData.push_back(up ? 1 : 0);
        packedData.push_back(down ? 1 : 0);
        packedData.push_back(left ? 1 : 0);
        packedData.push_back(right ? 1 : 0);
        packedData.push_back(shoot ? 1 : 0);
        return packedData;
    }

    void Unpack(const std::vector<unsigned char> &data) final
    {
        if (data.size() != 5)
        {
            std::cerr << "Invalid data size for unpacking." << std::endl;
            return;
        }

        up = data[0] != 0;
        down = data[1] != 0;
        left = data[2] != 0;
        right = data[3] != 0;
        shoot = data[4] != 0;
    }

    bool up;
    bool down;
    bool left;
    bool right;
    bool shoot;
};

struct PositionContainer : public IContainer
{
    std::vector<unsigned char> Pack() final
    {
        std::vector<unsigned char> packedData;
        packedData.push_back(id >> 24);
        packedData.push_back(id >> 16);
        packedData.push_back(id >> 8);
        packedData.push_back(id);
        packedData.push_back(x);
        packedData.push_back(y);
        return packedData;
    }

    void Unpack(const std::vector<unsigned char> &data) final
    {
        if (data.size() != 6)
        {
            std::cerr << "Invalid data size for unpacking." << std::endl;
            return;
        }

        id = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
        x = data[4];
        y = data[5];
    }

    unsigned int id;
    float x;
    float y;
};

#endif /* !CONTAINERS_HPP_ */
