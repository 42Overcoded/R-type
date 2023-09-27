#include <SFML/Graphics.hpp>

// void box_system(registry &r) {
//     /**
//      * @brief Setting a box system
//      * 
//      * @param r The registry where are stored the components
//      * 
//      * @return void Do not return anything
//     */
//     auto const &box = r.get_components<Component::box>();
//     auto const &position = r.get_components<Component::position>();
//     auto const &size = r.get_components<Component::size>();
//     auto const &color = r.get_components<Component::color>();
//     auto &window = r.get_components<Component::window>();
//     for (size_t i = 0; i < box.size(); ++i) {
//         if (window[i] && box[i] && position[i] && size[i] && color[i]) {
//             box[i].x = position[i].x;
//             box[i].y = position[i].y;
//             box[i].width = size[i].width;
//             box[i].height = size[i].height;
//             box[i].color = color[i].color;
//         }
//     }
// }

// void text_system(registru &r) {
//     /**
//      * @brief Setting a text system
//      * 
//      * @param r The registry where are stored the components
//      * 
//      * @return void Do not return anything
//     */
//     auto const &text = r.get_components<Component::text>();
//     auto const &position = r.get_components<Component::position>();
//     auto const &font_size = r.get_components<Component::font_size>();
//     auto const &color = r.get_components<Component::color>();
//     auto const &text_content = r.get_components<Component::text_content>();
//     auto &window = r.get_components<Component::window>();
//     for (size_t i = 0; i < text.size(); ++i) {
//         if (window[i] && text[i] && position[i] && color[i] && text_content[i]) {
//             text[i].x = position[i].x;
//             text[i].y = position[i].y;
//             text[i].font_size = font_size[i].font_size;
//             text[i].color = color[i].color;
//             text[i].text_content = text_content[i].text_content;
//         }
//     }
// }

/**
 * @brief Setting a draw system
 * 
 * @param r The registry where are stored the components
 * 
 * @return void Do not return anything
*/
void draw_system(registry &r) {
    auto const &window = r.get_components<Component::window>();
    auto const &position = r.get_components<Component::position>();
    auto const &box = r.get_components<Component::box>();
    auto const &text = r.get_components<Component::text>();
    auto &local_window;

    for (size_t i = 0; i < window.size(); ++i) {
        if (window[i]) {
            local_window = window[i];
        }
    }
    local_window.clear()
    for (size_t i = 0; i < position.size(); ++i) {
        if (box[i] && position[i]) {
            sf::RectangleShape local_box(sf::Vector2f(box[i].width, box[i].height));
            local_box.setPosition(position[i].x, position[i].y);
            local_box.setFillColor(box[i].color);
            local_window.draw(local_box);
        }
        else if (text[i] && position[i]) {
            sf::Font font;
            font.loadFromFile("src/client/graphics/arial.ttf");
            sf::Text local_text(text[i].text_content, font, text[i].font_size);
            local_text.setPosition(position[i].x, position[i].y);
            local_text.setFillColor(text[i].color);
            local_window.draw(local_text);
        }
    }
    local_window.display();
}

/**
 * @brief Setting a position system
 * 
 * @param r The registry where are stored the components
 * 
 * @return void Do not return anything
*/
void position_system(registry &r) {
    auto const &position = r.get_components<Component::position>();
    auto const &velocity = r.get_components<Component::velocity>();

    for (size_t i = 0; i < position.size(); ++i) {
        if (position[i] && velocity[i]) {
            position[i].x += velocity[i].x;
            position[i].y += velocity[i].y;
        }
    }
}

/**
 * @brief Setting a control system
 * 
 * @param r The registry where are stored the components
 * 
 * @return void Do not return anything
*/
void control_system(registry &r) {
    auto const &controllable = r.get_components<Component::controllable>();
    auto const &velocity = r.get_components<Component::velocity>();

    for (size_t i = 0; i < controllable.size(); ++i) {
        if (controllable[i] && velocity[i]) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                velocity[i].y = -1;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                velocity[i].y = 1;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                velocity[i].x = -1;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                velocity[i].x = 1;
            }
            else {
                velocity[i].x = 0;
                velocity[i].y = 0;
            }
        }
    }
}

int main() {
    // sf::RenderWindow window(sf::VideoMode(1920, 1080), "Ma Interface Graphique");

    // sf::RectangleShape box(sf::Vector2f(200, 50));
    // box.setPosition(300, 250);
    // box.setFillColor(sf::Color::Blue);

    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear();
    //     window.draw(box);
    //     window.display();
    // }

    return 0;
}
