/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** client
*/

#include <cstddef>
#include <iostream>
#include "../ecs/Registry.hpp"
#include "../gameEngine/GameEngine.hpp"
#include "../network/Protocol.hpp"

int main(int ac, char **av) {
    unsigned int serverPort = Network::DefaultPort;
    std::string serverIp = Network::DefaultIp;

    if (ac > 3) {
        std::cerr << "Usage: ./r-type_server serverPort serverIp" << std::endl;
        return 84;
    } else if (ac == 3) {
        try {
            serverPort = std::stoi(av[1]);
        } catch (std::exception &e) {
            std::cerr << "Error: port must be a number" << std::endl;
            return 84;
        }
        serverIp = av[2];
    } else {
        std::cout << "No port specified, using default port: " << Network::DefaultPort << std::endl;
    }
    registry r;
    gameEngine game(r, CLIENT/*, serverPort, serverIp*/);

    game.musics.insert(std::make_pair("musicMenu", std::make_shared<sf::Music>()));
    game.musics.insert(std::make_pair("musicGame", std::make_shared<sf::Music>()));
    game.musics.insert(std::make_pair("musicScore", std::make_shared<sf::Music>()));

    game.soundBuffers.insert(std::make_pair("soundShoot", std::make_shared<sf::SoundBuffer>()));
    game.soundBuffers.insert(std::make_pair("soundPowerShoot", std::make_shared<sf::SoundBuffer>()));
    game.soundBuffers.insert(std::make_pair("soundExplosion", std::make_shared<sf::SoundBuffer>()));
    game.soundBuffers.insert(std::make_pair("soundExplosion2", std::make_shared<sf::SoundBuffer>()));
    game.soundBuffers.insert(std::make_pair("soundExplosion3", std::make_shared<sf::SoundBuffer>()));

    game.sounds.insert(std::make_pair("soundShoot", std::make_shared<sf::Sound>()));
    game.sounds.insert(std::make_pair("soundPowerShoot", std::make_shared<sf::Sound>()));
    game.sounds.insert(std::make_pair("soundExplosion", std::make_shared<sf::Sound>()));
    game.sounds.insert(std::make_pair("soundExplosion2", std::make_shared<sf::Sound>()));
    game.sounds.insert(std::make_pair("soundExplosion3", std::make_shared<sf::Sound>()));

    game.musics["musicMenu"]->openFromFile("assets/R-Type (Arcade Soundtrack) 01 Title.mp3");
    game.musics["musicGame"]->openFromFile("assets/R-Type (Arcade Soundtrack) 02 Opening - Battle Theme (Stage 1).mp3");
    game.musics["musicScore"]->openFromFile("assets/R-Type (Arcade Soundtrack) 13 Game Over.mp3");

    game.soundBuffers["soundShoot"]->loadFromFile("assets/star wars blaster sound effect.mp3");
    game.soundBuffers["soundPowerShoot"]->loadFromFile("assets/star wars dc 15s blaster rifle sound effect.mp3");
    game.soundBuffers["soundExplosion"]->loadFromFile("assets/explosion sound.mp3");
    game.soundBuffers["soundExplosion2"]->loadFromFile("assets/roblox rocket explosion sound.mp3");
    game.soundBuffers["soundExplosion3"]->loadFromFile("assets/Geometry Dash Death Sound Effect.mp3");

    game.sounds["soundShoot"]->setBuffer(*game.soundBuffers["soundShoot"]);
    game.sounds["soundPowerShoot"]->setBuffer(*game.soundBuffers["soundPowerShoot"]);
    game.sounds["soundExplosion"]->setBuffer(*game.soundBuffers["soundExplosion"]);
    game.sounds["soundExplosion2"]->setBuffer(*game.soundBuffers["soundExplosion2"]);
    game.sounds["soundExplosion3"]->setBuffer(*game.soundBuffers["soundExplosion3"]);

    game.musics["musicMenu"]->setVolume(30);
    game.musics["musicGame"]->setVolume(30);
    game.musics["musicScore"]->setVolume(30);

    game.sounds["soundShoot"]->setVolume(70);
    game.sounds["soundPowerShoot"]->setVolume(70);
    game.sounds["soundExplosion"]->setVolume(70);
    game.sounds["soundExplosion2"]->setVolume(70);
    game.sounds["soundExplosion3"]->setVolume(70);

    game.musics["musicMenu"]->setLoop(true);
    game.musics["musicScore"]->setLoop(false);
    game.musics["musicGame"]->setLoop(true);

    game.launch_game();
}
