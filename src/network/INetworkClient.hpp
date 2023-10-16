/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** INetworkClient
*/

#ifndef INETWORKCLIENT_HPP_
#define INETWORKCLIENT_HPP_
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include "Connection.hpp"
#include "Packet.hpp"

namespace Network {

template <typename T>
class PacketsQueue;

template <typename T>
class INetworkClient
{
public:
    INetworkClient() : socket_(ioContext_)
    {
    }
    virtual ~INetworkClient()
    {
        Disconnect();
    }

    bool Connect(const std::string serverIp, const uint16_t serverPort)
    {
        try
        {
            boost::asio::ip::udp::resolver resolver(ioContext_);
            boost::asio::ip::udp::resolver::results_type endpoints = resolver.resolve(serverIp, std::to_string(serverPort));
            connection_ = std::make_unique<Connection<T>>(Connection<T>::Owner::Client, ioContext_, boost::asio::ip::udp::socket(ioContext_), packetsInQueue_);
            connection_->ConnectToServer(endpoints);
            threadContext_ = std::thread([this]() { ioContext_.run(); });
        }
        catch (const std::exception &e)
        {
            std::cerr << "[CLIENT] Exception: " << e.what() << std::endl;
            return false;
        }
        std::cout << "[CLIENT] Started" << std::endl;
        return true;
    }

    void Disconnect()
    {
        if (IsConnected())
        {
            connection_->Disconnect();
        }
        ioContext_.stop();
        if (threadContext_.joinable())
        {
            threadContext_.join();
        }
        connection_.release();
    }

    bool IsConnected() const
    {
        if (connection_)
        {
            return connection_->IsConnected();
        }
        return false;
    }

    void SendToServer(const Packet<T> &packet)
    {
        if (IsConnected())
        {
            connection_->SendPacket(packet);
        }
    }

    PacketsQueue<OwnedPacket<T>> &Incoming()
    {
        return packetsInQueue_;
    }

protected:
    boost::asio::io_context ioContext_;
    std::thread threadContext_;
    boost::asio::ip::udp::socket socket_;
    std::unique_ptr<Connection<T>> connection_;

private:
    PacketsQueue<OwnedPacket<T>> packetsInQueue_;
};
};  // namespace Network

#endif /* !INETWORKCLIENT_HPP_ */
