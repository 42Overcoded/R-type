/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** movements
*/

#include "../../GameEngine.hpp"

void gameEngine::movement_system(registry &r)
{
    auto &control = r.get_components<Control>();
    auto &speed = r.get_components<Speed>();
    auto &rect = r.get_components<Rect>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (control[i].has_value() && speed[i].has_value()) {
            speed[i]->speedx = 0.0f;
            speed[i]->speedy = 0.0f;

            if (control[i]->up == true) {
                speed[i]->speedy = -0.5f;
                rect[i]->left = rect[i]->baseLeft + 132;
            }
            if (control[i]->down == true) {
                speed[i]->speedy = 0.5f;
                rect[i]->left = rect[i]->baseLeft;
            }
            if (control[i]->left == true) {
                speed[i]->speedx = -0.5f;
            }
            if (control[i]->right == true) {
                speed[i]->speedx = 0.5f;
                rect[i]->left = rect[i]->baseLeft + 66;
            }
            if (!control[i]->up && !control[i]->down && !control[i]->right) {
                rect[i]->left = rect[i]->baseLeft + 33;
            }
        }
    }
}
