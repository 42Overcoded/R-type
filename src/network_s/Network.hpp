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
#include <cstdint>
#include <ctime>
#include <deque>
#include <iostream>
#include <string>
#include "../ecs/Registry.hpp"

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
    bool rawSendPacket(boost::asio::const_buffer data, std::uint64_t packetId, std::uint8_t flag);
    bool rawReceivePacket();

private:
    std::vector<unsigned char> availablePacket;
    std::deque<unsigned char> bufferedBytes;
    boost::asio::io_context io_context_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
};

const unsigned int DefaultPort = 4242;
const std::size_t packetHeaderSize = sizeof(std::uint8_t) +   // Packet flags
                                     sizeof(std::uint64_t) +  // Packet ID
                                     sizeof(std::uint64_t);   // Packet data size
const unsigned int PacketElemNbr = 4;

#endif
