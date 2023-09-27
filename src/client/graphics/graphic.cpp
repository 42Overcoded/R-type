#include <SFML/Graphics.hpp>

void box_position_system(registry &r) {
    auto const &box = r.get_components<component::box>();
    auto const &position = r.get_components<component::position>();
    auto &window = r.get_components<component::window>();
    for (size_t i = 0; i < box.size(); ++i) {
        if (window[i] && box[i] && position[i]) {
            box[i].x = position[i].x;
            box[i].y = position[i].y;
        }
    }
}

void draw_system(registry &r) {
    auto const &window = r.get_components<component::window>();
    if (window) {
        window.draw()
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Ma Interface Graphique");

    sf::RectangleShape box(sf::Vector2f(200, 50));
    box.setPosition(300, 250);
    box.setFillColor(sf::Color::Blue);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(box);
        window.display();
    }

    return 0;
}
