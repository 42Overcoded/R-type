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

UdpServer::UdpServer(unsigned int portNumber)
    : io_context_()
    , socket_(io_context_, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), portNumber))
{
    start_receive();
}

UdpServer::~UdpServer()
{
    socket_.close();
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
    if (!error || error == boost::asio::error::message_size)
    {
        std::string curr_client = endpointToString(remote_endpoint_);
        if (clients.find(curr_client) == clients.end())
        {
            clients.insert(std::make_pair(curr_client, Client(remote_endpoint_, clienId++)));
        }
        rawReceivePacket(curr_client);
        start_receive();
    }
}

void UdpServer::handle_send(
    const std::array<boost::asio::const_buffer, PacketElemNbr> &buffersToSend,
    const boost::system::error_code &send_error,
    std::size_t bytes_transferred)
{
}

void UdpServer::rawReceivePacket(std::string curr_client)
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
        clients[curr_client].availablePacket.push_back(Packet(
            receivedFlags, receivedPacketId, receivedDataSize,
            std::vector<unsigned char>(
                recv_buffer_.begin() + (packetHeaderSize),
                recv_buffer_.begin() + (packetHeaderSize + receivedDataSize))));
    }
}

bool UdpServer::rawSendPacket(
    boost::asio::const_buffer data,
    std::uint64_t packetId,
    std::uint8_t flag,
    std::string destClient)
{
    std::uint64_t dataSize = static_cast<std::uint64_t>(data.size());
    std::array<boost::asio::const_buffer, PacketElemNbr> buffersToSend = {
        {{&flag, sizeof(flag)}, {&packetId, sizeof(packetId)}, {&dataSize, sizeof(dataSize)}, data}};
    boost::system::error_code send_error;
    this->socket_.async_send_to(
        buffersToSend, clients[destClient].endpoint, {},
        boost::bind(
            &UdpServer::handle_send, this, buffersToSend, send_error,
            boost::asio::placeholders::bytes_transferred));
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

std::string UdpServer::endpointToString(boost::asio::ip::udp::endpoint endpoint)
{
    std::string ipAddress  = endpoint.address().to_string();
    std::string portNumber = std::to_string(endpoint.port());

    return ipAddress + ":" + portNumber;
}

void UdpServer::sendPacket(std::string client, flag flag, std::vector<unsigned char> data)
{
    std::uint64_t packetId = 0;
    if (clients.find(client) != clients.end())
    {
        rawSendPacket(
            boost::asio::const_buffer(&data.at(0), data.size()), packetId, flag, client);
    }
}

void UdpServer::sendToAll(flag flag, std::vector<unsigned char> data)
{
    std::uint64_t packetId = 0;
    for (auto &client : clients)
    {
        rawSendPacket(
            boost::asio::const_buffer(&data.at(0), data.size()), packetId, flag, client.first);
    }
}