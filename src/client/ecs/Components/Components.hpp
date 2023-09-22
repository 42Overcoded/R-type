/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

class Speed {
    public:
        Speed(int speed);
        void setSpeed(int speed);
        ~Speed();
    protected:
        int _speed;
    private:
};

class Position {
    public:
        Position(int x, int y);
        void setPosition(int x, int y);
        ~Position();
    private:
        int _x;
        int _y;
};

#endif /* !COMPONENTS_HPP_ */
