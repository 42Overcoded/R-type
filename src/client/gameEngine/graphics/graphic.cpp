// /*
// ** EPITECH PROJECT, 2023
// ** R-type
// ** File description:
// ** graphic
// */

// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>
// #include <iostream>
// #include "ecs/Registry.hpp"
// #include "gameEngine/gameEngine.hpp"
// #include "ecs/ComponentsArray/Components/Components.hpp"


// /**
//  * @brief Setting a draw system
//  * 
//  * @param r The registry where are stored the components
//  * 
//  * @return void Do not return anything
// */
// void draw_system(registry &r) {
//     auto const &window = r.get_components<Component::window>();
//     auto const &position = r.get_components<Component::position>();
//     auto const &box = r.get_components<Component::box>();
//     auto const &text = r.get_components<Component::text>();
//     sf::RenderWindow &local_window;

//     for (size_t i = 0; i < window.size(); ++i) {
//         if (window[i]) {
//             local_window = window[i];
//         }
//     }
//     local_window.clear()
//     for (size_t i = 0; i < position.size(); ++i) {
//         if (box[i] && position[i]) {
//             sf::RectangleShape local_box(sf::Vector2f(box[i].width, box[i].height));
//             local_box.setPosition(position[i].x, position[i].y);
//             local_box.setFillColor(box[i].color);
//             local_window.draw(local_box);
//         } else if (text[i] && position[i]) {
//             sf::Font font;
//             font.loadFromFile(text[i].font_path);
//             sf::Text local_text(text[i].text_content, font, text[i].font_size);
//             local_text.setPosition(position[i].x, position[i].y);
//             local_text.setFillColor(text[i].color);
//             local_window.draw(local_text);
//         }
//     }
//     local_window.display();
// }

// /**
//  * @brief Setting a position system
//  * 
//  * @param r The registry where are stored the components
//  * 
//  * @return void Do not return anything
// */
// void position_system(registry &r) {
//     auto const &position = r.get_components<Component::position>();
//     auto const &velocity = r.get_components<Component::velocity>();

//     for (size_t i = 0; i < position.size(); ++i) {
//         if (position[i] && velocity[i]) {
//             position[i].x += velocity[i].x;
//             position[i].y += velocity[i].y;
//         }
//     }
// }

// /**
//  * @brief Setting a control system
//  * 
//  * @param r The registry where are stored the components
//  * 
//  * @return void Do not return anything
// */
// void control_system(registry &r) {
//     auto const &controllable = r.get_components<Component::controllable>();
//     auto const &velocity = r.get_components<Component::velocity>();

//     for (size_t i = 0; i < controllable.size(); ++i) {
//         if (controllable[i] && velocity[i]) {
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//                 velocity[i].y = -1;
//             } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//                 velocity[i].y = 1;
//             } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//                 velocity[i].x = -1;
//             } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//                 velocity[i].x = 1;
//             } else {
//                 velocity[i].x = 0;
//                 velocity[i].y = 0;
//             }
//         }
//     }
// }

// /**
//  * @brief Setting a logic system
//  * 
//  * @param r The registry where are stored the components
//  * 
//  * @return void Do not return anything
// */
// void logic_system(registry &r) {
//     auto const position = r.get_components<Component::position>();
//     auto const velocity = r.get_components<Component::velocity>();

//     for (size_t i = 0; i < position.size() && i < velocity.size(); ++i) {
//         auto const &pos = position[i];
//         auto const &vel = velocity[i];

//         if (pos && vel) {
//             std::cout << "Position: " << pos.x << ", " << pos.y << std::endl;
//             std::cout << "Velocity: " << vel.x << ", " << vel.y << std::endl;
//         }
//     }
// }
