/*
** EPITECH PROJECT, 2023
** CLIENT
** File description:
** CLIENT
*/
#include "Network.hpp"
#include "TestClassPlayer.hpp"
#include "TestStructPlayer.hpp"

#include <iostream>
#include <sstream>

#include "../ecs/ComponentsArray/Components/Components.hpp"

Network::Network(std::string ipServer, int portServer)
{
    _ipServer = ipServer;
    _portServer = portServer;

    ptrIOcontext = new boost::asio::io_context;

    ptrCliSocket = new boost::asio::ip::udp::socket(*ptrIOcontext, boost::asio::ip::udp::v4());
    ptrServEndpoint = new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(_ipServer), _portServer);

    ptrError = new boost::system::error_code;
}

Network::~Network()
{
    if (ptrIOcontext != NULL) {
        ptrIOcontext->stop();
        delete ptrIOcontext;
    }

    if (ptrCliSocket != NULL) {
        ptrCliSocket->close();
        delete ptrCliSocket;
    }
    if (ptrServEndpoint != NULL)
        delete ptrServEndpoint;
    if (ptrError != NULL)
        delete ptrError;
}

int Network::send_info_to_server(void *strucToServer)
{
    struct Test2 {
        int x;
    };
    struct Test {
        void *ptrTest;
        char arr[10];
        int number;
        Test2 test2;
    };
    Test2 test2 = {66};
    Test test = {};
    test.ptrTest = &test;
    strcpy(test.arr, "yolo2");
    test.test2 = test2;
    ptrCliSocket->send_to(boost::asio::buffer(&test, sizeof(test)), *ptrServEndpoint, 0, *ptrError);

    ptrCliSocket->send_to(boost::asio::buffer(strucToServer, sizeof(ComponentOUT)), *ptrServEndpoint, 0, *ptrError);
    return 0;
}
