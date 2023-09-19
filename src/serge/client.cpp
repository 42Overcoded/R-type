/*
** EPITECH PROJECT, 2023
** SERGE
** File description:
** SERGE
*/
#include <boost/asio.hpp>
#include <iostream>

int main()
{
    boost::system::error_code ec;
    
    boost::asio::io_context context;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("127.0.0.1", ec), 80);

    boost::asio::ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);

    if (!ec) {
        std::cout << "Connexion réussie" << std::endl;
    } else {
        std::cout << "Connexion échouée: " << ec.message() << std::endl;
    }
    return 0;
}
