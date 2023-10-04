/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** network
*/
#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <boost/asio.hpp>

class Network {
    private:
        boost::asio::io_context ioContext;
        boost::asio::ip::udp::socket servSocket;
        boost::asio::ip::udp::endpoint cliEndpoint;
        boost::system::error_code error;

        char cliMessage[1000];
        size_t totalReceived = 0;

    public:
        Network(int portNumber);
        ~Network();

        int listen_info_from_clients(void);
        std::string make_daytime_string();
};

#endif /* !NETWORK_HPP_ */
