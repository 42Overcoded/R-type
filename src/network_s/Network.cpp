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
#include "../ecs/Registry.hpp"

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

bool UdpServer::rawReceivePacket()
{
    std::uint8_t receivedFlags;
    std::uint64_t receivedPacketId;
    std::uint64_t receivedDataSize;
    std::array<boost::asio::mutable_buffer, 3> buffersToFill = {
        {{&receivedFlags, sizeof(receivedFlags)},
         {&receivedPacketId, sizeof(receivedPacketId)},
         {&receivedDataSize, sizeof(receivedDataSize)}}};

    std::array<unsigned char, packetHeaderSize> packetHeaderBytes;
    std::copy(
        bufferedBytes.begin(), bufferedBytes.begin() + packetHeaderSize, packetHeaderBytes.begin());
    auto asioBufferCopiedByteCount = boost::asio::buffer_copy(
        buffersToFill,
        boost::asio::const_buffer(&packetHeaderBytes.at(0), packetHeaderBytes.size()));
    if (receivedDataSize != 0)
    {
        availablePacket.insert(
            availablePacket.begin(), bufferedBytes.begin() + (packetHeaderSize),
            bufferedBytes.begin() + (packetHeaderSize + receivedDataSize));
    }
}

bool UdpServer::rawSendPacket(
    boost::asio::const_buffer data, std::uint64_t packetId, std::uint8_t flag)
{
    std::uint64_t dataSize = static_cast<std::uint64_t>(data.size());
    std::array<boost::asio::const_buffer, 8> buffersToSend = {
        {{&flag, sizeof(flag)}, {&packetId, sizeof(packetId)}, {&dataSize, sizeof(dataSize)}, data}};
    boost::system::error_code send_error;
    this->socket_.send_to(buffersToSend, remote_endpoint_, {}, send_error);
    return !send_error.failed();
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
