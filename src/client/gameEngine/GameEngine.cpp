/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#include "GameEngine.hpp"
#include <optional>

void gameEngine::launch_game() {
    std::cout << "Game launched" << std::endl;
    // entity_t window = this->_registry.spawn_entity();
    // this->_registry.add_component<Window>(window, Window());
    // auto &window_component = this->_registry.get_components<Window>();
    // window_component[window].width = 1920;
    // window_component[window].height = 1080;
    // window_component[window].max_fps = 60;
    // window_component[window].window.create(sf::VideoMode(window_component[window].width, window_component[window].height), "R-Type", sf::Style::Fullscreen);
    // while (window_component[window].window.isOpen()) {
    //     sf::Event event;
    //     while (window_component[window].window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed)
    //             window_component[window].window.close();
    //     }
    //     window_component[window].window.clear();
    //     window_component[window].window.display();
    // }
}
