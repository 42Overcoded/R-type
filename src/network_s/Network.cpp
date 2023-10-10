/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/

#include "Network.hpp"
#include <ctime>
#include <iostream>
#include <sstream>

UdpServer::UdpServer(unsigned int portNumber)
    : io_context_()
    , socket_(io_context_, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portNumber))
{
    start_receive();
}

void UdpServer::start_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(
            &UdpServer::handle_receive, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void UdpServer::handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (!error)
    {
        boost::shared_ptr<std::string> message(new std::string(make_daytime_string()));

        socket_.async_send_to(
            boost::asio::buffer(*message), remote_endpoint_,
            boost::bind(
                &UdpServer::handle_send, this, message, boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));

        start_receive();
    }
}

void UdpServer::handle_send(
    boost::shared_ptr<std::string> message,
    const boost::system::error_code &error,
    std::size_t bytes_transferred)
{
}

std::string UdpServer::make_daytime_string()
{
    std::time_t now = time(0);
    return ctime(&now);
}

void UdpServer::run()
{
    io_context_.run();
}
