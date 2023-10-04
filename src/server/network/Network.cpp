/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/
#include "Network.hpp"
#include "TestClassPlayer.hpp"

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

#include <ctime>
#include <iostream>
#include <sstream>


Network::Network(int portNumber)
    : servSocket(ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portNumber))
    , cliEndpoint()
    , error()
{
}

Network::~Network()
{
    ioContext.stop();
    servSocket.close();
}

int Network::listen_info_from_clients(void)
{
    testPlayer TestPlayer;
    try
    {
        while (true)
        {
            totalReceived = servSocket.receive_from(boost::asio::buffer(cliMessage), cliEndpoint, 0, error);
            if (error.failed() == true && error != boost::asio::error::message_size)
            {
                std::cout << "Erreur de connexion: " << error.message() << std::endl;
                break;
            }

            std::stringstream strstr;
            strstr << cliMessage;
            boost::archive::text_iarchive ia(strstr);
            ia >> TestPlayer;

            boost::array<char, 1> recv_buf;
            boost::asio::ip::udp::endpoint remote_endpoint;
            servSocket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);

            std::string message = make_daytime_string();

            boost::system::error_code ignored_error;
            servSocket.send_to(boost::asio::buffer(message), remote_endpoint, 0, ignored_error);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

std::string Network::make_daytime_string()
{
    std::time_t now = time(0);
    return ctime(&now);
}
