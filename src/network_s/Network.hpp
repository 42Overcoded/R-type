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
        boost::asio::io_context *ptrIOcontext;
        boost::asio::ip::udp::socket *ptrServSocket;
        boost::asio::ip::udp::endpoint *ptrCliEndpoint;
        boost::system::error_code *ptrError;

        char cliMessage[1000];
        size_t totalReceived;
    public:
        Network();
        ~Network();
        int create_server(int portServer = 4242);
        int listen_info_from_clients(void);
};

#endif /* !NETWORK_HPP_ */
