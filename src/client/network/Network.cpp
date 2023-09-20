/*
** EPITECH PROJECT, 2023
** CLIENT
** File description:
** CLIENT
*/
#include "network.hpp"

Network::Network() {

};

Network::~Network() {

}

int Network::create_client(void) {
    boost::asio::io_context io_context;
    boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::v4());

    boost::asio::ip::udp::endpoint server_endpoint(boost::asio::ip::address::from_string("10.15.193.252"), 9876);

    std::string message = "Bonjour, serveur!";
    
    socket.send_to(boost::asio::buffer(message), server_endpoint);

    return 0;
}
