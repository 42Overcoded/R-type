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
#include <vector>
#include "../ecs/Registry.hpp"
#include <unordered_map>

const unsigned int DefaultPort     = 4242;
const std::size_t packetHeaderSize = sizeof(std::uint8_t) +   // Packet flags
                                     sizeof(std::uint64_t) +  // Packet ID
                                     sizeof(std::uint64_t);   // Packet data size
const unsigned int PacketElemNbr = 4;
enum flag {
    NONE = 0,
    CONNECT = 1,
    DISCONNECT = 2,
    CONTROLLER = 3,
    POSITION = 4,
    START = 5,
    END = 6,
};

class Packet {
public:
    Packet() = default;
    Packet(std::uint8_t flags, std::uint64_t id, std::uint64_t dataSize, std::vector<unsigned char> data)
        : flags(flags)
        , id(id)
        , dataSize(dataSize)
        , data(data){};
    ~Packet() = default;

    std::uint8_t flags;
    std::uint64_t id;
    std::uint64_t dataSize;
    std::vector<unsigned char> data;
};

class UdpServer
{
public:
    class Client
    {
    public:
        Client() = default;
        Client(boost::asio::ip::udp::endpoint endpoint, std::uint64_t id)
            : endpoint(endpoint){};
        ~Client() = default;

        std::uint64_t id;
        boost::asio::ip::udp::endpoint endpoint;
        std::vector<Packet> availablePacket;
        std::deque<unsigned char> bufferedBytes;
    };

public:
    UdpServer(unsigned int portNumber);
    void run();
    void sendPacket(std::string client, flag flag, std::vector<unsigned char> data);
    void sendToAll(flag flag, std::vector<unsigned char> data);

    std::unordered_map<std::string, Client> clients;

private:
    std::string make_daytime_string();
    void start_receive();
    void handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred);
    void handle_send(
    const std::array<boost::asio::const_buffer, PacketElemNbr>& buffersToSend,
    const boost::system::error_code& send_error,
    std::size_t bytes_transferred);
    bool rawSendPacket(boost::asio::const_buffer data, std::uint64_t packetId, std::uint8_t flag, std::string destClient);
    void rawReceivePacket(std::string curr_client);
    std::string endpointToString(boost::asio::ip::udp::endpoint endpoint);

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
    unsigned int clienId;
};

#endif
