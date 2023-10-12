/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** SERVER
*/

#include "Network.hpp"
#include <cinttypes>
#include <ctime>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "../ecs/Registry.hpp"

UdpClient::UdpClient(unsigned int serverPort, std::string serverIp)
    : io_context_()
    , socket_(io_context_, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0))
{
    boost::asio::ip::udp::resolver resolver(io_context_);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), serverIp, std::to_string(serverPort));
    boost::asio::ip::udp::resolver::iterator iterator = resolver.resolve(query);
    remote_endpoint_ = *iterator;
    start_receive();
}

UdpClient::~UdpClient()
{
    socket_.close();
}

void UdpClient::start_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(
            &UdpClient::handle_receive, this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void UdpClient::handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size)
    {
        server.endpoint = remote_endpoint_;
        rawReceivePacket();
        start_receive();
    }
}

void UdpClient::handle_send(
    const std::array<boost::asio::const_buffer, PacketElemNbr> &buffersToSend,
    const boost::system::error_code &send_error,
    std::size_t bytes_transferred)
{
}

void UdpClient::rawReceivePacket()
{
    std::uint8_t receivedFlags;
    std::uint64_t receivedPacketId;
    std::uint64_t receivedDataSize;
    std::array<boost::asio::mutable_buffer, PacketElemNbr - 1> buffersToFill = {
        {{&receivedFlags, sizeof(receivedFlags)},
         {&receivedPacketId, sizeof(receivedPacketId)},
         {&receivedDataSize, sizeof(receivedDataSize)}}};
    std::array<unsigned char, packetHeaderSize> packetHeaderBytes;

    std::copy(
        recv_buffer_.begin(), recv_buffer_.begin() + packetHeaderSize, packetHeaderBytes.begin());
    auto asioBufferCopiedByteCount = boost::asio::buffer_copy(
        buffersToFill,
        boost::asio::const_buffer(&packetHeaderBytes.at(0), packetHeaderBytes.size()));
    if (receivedDataSize != 0)
    {
        server.availablePacket.push_back(Packet(
            receivedFlags, receivedPacketId, receivedDataSize,
            std::vector<unsigned char>(
                recv_buffer_.begin() + (packetHeaderSize),
                recv_buffer_.begin() + (packetHeaderSize + receivedDataSize))));
    }
}

bool UdpClient::rawSendPacket(
    boost::asio::const_buffer data,
    std::uint64_t packetId,
    std::uint8_t flag)
{
    std::uint64_t dataSize = static_cast<std::uint64_t>(data.size());
    std::array<boost::asio::const_buffer, PacketElemNbr> buffersToSend = {
        {{&flag, sizeof(flag)}, {&packetId, sizeof(packetId)}, {&dataSize, sizeof(dataSize)}, data}};
    boost::system::error_code send_error;
    this->socket_.async_send_to(
        buffersToSend, server.endpoint, {},
        boost::bind(
            &UdpClient::handle_send, this, buffersToSend, send_error,
            boost::asio::placeholders::bytes_transferred));
    return !send_error.failed();
}

std::string UdpClient::make_daytime_string()
{
    std::time_t now = time(0);
    return ctime(&now);
}

void UdpClient::run()
{
    io_context_.run();
}

void UdpClient::sendPacket(flag flag, std::vector<unsigned char> data)
{
    std::uint64_t packetId = 0;

    rawSendPacket(boost::asio::const_buffer(&data.at(0), data.size()), packetId, flag);
}
