/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkClient
*/

#ifndef NETWORKCLIENT_HPP_
#define NETWORKCLIENT_HPP_
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
class NetworkClient
{
public:
    NetworkClient() : socket_(ioContext_)
    {
    }
    virtual ~NetworkClient()
    {
        Disconnect();
    }

    bool Connect(const std::string serverIp, const uint16_t serverPort)
    {
        try
        {
            boost::asio::ip::udp::resolver resolver(ioContext_);
            boost::asio::ip::udp::resolver::query query(
                boost::asio::ip::udp::v4(), serverIp, std::to_string(serverPort));
            boost::asio::ip::udp::resolver::iterator iterator = resolver.resolve(query);
            boost::asio::connect(socket_, iterator);
            connection_    = std::make_unique<Connection<T>>(std::move(socket_), packetsInQueue_);
            threadContext_ = std::thread([this]() { ioContext_.run(); });
        }
        catch (const std::exception &e)
        {
            std::cerr << "[CLIENT] Exception: " << e.what() << std::endl;
            return false;
        }
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

#endif /* !NETWORKCLIENT_HPP_ */
