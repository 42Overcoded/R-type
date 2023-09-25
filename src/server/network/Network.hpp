/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** network
*/
#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <iostream>
#include <boost/asio.hpp>

class Network {
    private:
        std::shared_ptr<boost::asio::ip::udp::socket> ptrServSocket;
        std::shared_ptr<boost::asio::ip::udp::endpoint> ptrCliEndpoint;
        std::shared_ptr<boost::system::error_code> ptrError;

        char cliMessage[500];
        size_t totalReceived;
    public:
        Network();
        ~Network();
        int create_server(int portServer = 4242);
        int listen_info_from_clients(void);
};

#endif /* !NETWORK_HPP_ */
