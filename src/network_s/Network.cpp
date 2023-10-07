/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/
#include "Network.hpp"
#include "TestClassPlayer.hpp"
#include "TestStructPlayer.hpp"
#include "../ecs/ComponentsArray/Components/Components.hpp"

#include <iostream>
#include <sstream>


Network::Network()
{
    std::cout << "Message perso" << std::endl;

    totalReceived = 0;
    cliMessage[500] = 0;
}

Network::~Network()
{
    if (ptrIOcontext != NULL) {
        ptrIOcontext->stop();
        delete ptrIOcontext;
    }

    if (ptrServSocket != NULL) {
        ptrServSocket->close();
        delete ptrServSocket;
    }
    if (ptrCliEndpoint != NULL)
        delete ptrCliEndpoint;
    if (ptrError != NULL)
        delete ptrError;
}

int Network::create_server(int portServer)
{
    ptrIOcontext = new boost::asio::io_context;
    ptrServSocket = new boost::asio::ip::udp::socket(*ptrIOcontext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portServer));

    ptrCliEndpoint = new boost::asio::ip::udp::endpoint;
    ptrError = new boost::system::error_code;

    return 0;
}

int Network::listen_info_from_clients(void)
{
    //void *ptrStruct = NULL;
    //struct Damage damage;
    //struct ComponentOUT componentOUT;
    ComponentOUT componentOUT;

    struct Test2 {
        int x;
    };
    struct Test {
        void *ptrTest;
        char arr[10];
        int number;
        Test2 test2;
    };
    Test test;

    while (true) {
        //totalReceived = ptrServSocket->receive_from(boost::asio::buffer(ptrStruct, sizeof(ptrStruct)), *ptrCliEndpoint, 0, *ptrError);
        totalReceived = ptrServSocket->receive_from(boost::asio::buffer(&test, sizeof(test)), *ptrCliEndpoint, 0, *ptrError);

        totalReceived = ptrServSocket->receive_from(boost::asio::buffer(&componentOUT, sizeof(componentOUT)), *ptrCliEndpoint, 0, *ptrError);

        if (ptrError->failed() == true && *ptrError != boost::asio::error::message_size) {
            std::cout << "Erreur de connexion: " << ptrError->message() << std::endl;
            break;
        }

        // if (static_cast<Speed*>(ptrStruct) != NULL)
        //     struct Speed speed = *static_cast<Speed*>(ptrStruct);
        // if (static_cast<Position*>(ptrStruct) != NULL)
        //     struct Position position = *static_cast<Position*>(ptrStruct);
        // if (static_cast<Sprite*>(ptrStruct) != NULL)
        //     struct Sprite sprite = *static_cast<Sprite*>(ptrStruct);
        // if (static_cast<Player*>(ptrStruct) != NULL)
        //     struct Player player = *static_cast<Player*>(ptrStruct);
        // if (static_cast<Enemy*>(ptrStruct) != NULL)
        //     struct Enemy enemy = *static_cast<Enemy*>(ptrStruct);
        // if (static_cast<Bullet*>(ptrStruct) != NULL)
        //     struct Bullet bullet = *static_cast<Bullet*>(ptrStruct);
        // if (static_cast<Tag*>(ptrStruct) != NULL)
        //     struct Tag tag = *static_cast<Tag*>(ptrStruct);
        // if (static_cast<Health*>(ptrStruct) != NULL)
        //     struct Health health = *static_cast<Health*>(ptrStruct);
        // if (static_cast<Damage*>(ptrStruct) != NULL)
        //     struct Damage damage = *static_cast<Damage*>(ptrStruct);
        // if (static_cast<Score*>(ptrStruct) != NULL)
        //     struct Score score = *static_cast<Score*>(ptrStruct);
        // if (static_cast<Text*>(ptrStruct) != NULL)
        //     struct Text text = *static_cast<Text*>(ptrStruct);
        // if (static_cast<Drawable*>(ptrStruct) != NULL)
        //     struct Drawable drawable = *static_cast<Drawable*>(ptrStruct);
        // if (static_cast<Control*>(ptrStruct) != NULL)
        //     struct Control control = *static_cast<Control*>(ptrStruct);
        // if (static_cast<Pattern*>(ptrStruct) != NULL)
        //     struct Pattern pattern = *static_cast<Pattern*>(ptrStruct);
        // if (static_cast<Hitbox*>(ptrStruct) != NULL)
        //     struct Hitbox hitbox = *static_cast<Hitbox*>(ptrStruct);


        //std::cout << componentOUT.nameStructToSend[0] << std::endl;
        //std::cout << componentOUT.nameStructToSend << std::endl;
        std::cout << test.arr << std::endl;
        std::cout << test.test2.x << std::endl;

        std::cout << componentOUT.nameStructToSend << std::endl;
        //if (componentOUT.nameStructToSend == "damage")
        if (strcmp(componentOUT.nameStructToSend, "damage") == 0)
            std::cout << componentOUT.damage.damage << std::endl;
        // std::cout << static_cast<Damage*>(componentOUT.ptrToStructToSend)->damage << std::endl;
    }
    return 0;
}
