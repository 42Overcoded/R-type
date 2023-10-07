/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Network
*/

#ifndef NETWORK_HPP
#define NETWORK_HPP
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <ctime>
#include <iostream>
#include <string>

class UdpServer
{
public:
    UdpServer(unsigned int portNumber);
    void run();

private:
    std::string make_daytime_string();
    void start_receive();
    void handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred);
    void handle_send(
        boost::shared_ptr<std::string> message,
        const boost::system::error_code &error,
        std::size_t bytes_transferred);

    boost::asio::io_context io_context_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
};

struct ITransmission
{
    unsigned int header;
    unsigned int size;
};

struct Transmission : ITransmission
{
};

#endif
