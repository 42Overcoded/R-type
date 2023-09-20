/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/
#include <iostream>
#include <boost/asio.hpp>

int main() {
    boost::asio::io_context io_context;
    
    boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 9876));

    while (true) {
        char data[1024];
        boost::asio::ip::udp::endpoint client_endpoint;
        boost::system::error_code error;

        size_t length = socket.receive_from(boost::asio::buffer(data), client_endpoint, 0, error);

        if (error && error != boost::asio::error::message_size) {
            std::cerr << "Erreur lors de la réception : " << error.message() << std::endl;
            break;
        }

        std::cout << "Message reçu du client : " << data << std::endl;
    }

    return 0;
}
