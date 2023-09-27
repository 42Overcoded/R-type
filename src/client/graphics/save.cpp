#include <SFML/Graphics.hpp>

int main() {
    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Ma Interface Graphique");

    // Créer un bouton
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setPosition(300, 250);
    button.setFillColor(sf::Color::Blue);

    // Créer le texte du bouton
    sf::Font font;
    font.loadFromFile("./Arial.ttf");
    sf::Text buttonText("Cliquez ici !", font, 20);
    buttonText.setPosition(310, 260);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Gérer le clic de souris
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f buttonPos = button.getPosition();
                sf::Vector2f buttonSize = button.getSize();

                if (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x &&
                    mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + buttonSize.y) {
                    // Le bouton a été cliqué !
                    button.setFillColor(sf::Color::Red);
                    buttonText.setString("Clic' effectué !");
                }
            }
        }

        window.clear();
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }

    return 0;
}
