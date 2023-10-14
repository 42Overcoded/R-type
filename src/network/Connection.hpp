/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <cstddef>
#include <iostream>
#include "PacketsQueue.hpp"
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/udp.hpp"
#include <sys/types.h>

namespace Network {

template <typename T>
class PacketHeader;

template <typename T>
class Packet;

template <typename T>
class PacketsQueue;

template <typename T>
class Connection : public std::enable_shared_from_this<Connection<T>>
{
public:
    enum class Owner
    {
        Server,
        Client
    };

    Connection(
        Owner ownerType,
        boost::asio::io_context &ioContext,
        boost::asio::ip::udp::socket socket,
        PacketsQueue<Packet<T>> &packetsInQueue)
        : ioContext_(ioContext), socket_(std::move(socket)), packetsInQueue_(packetsInQueue)
    {
        ownerType_ = ownerType;
    }
    virtual ~Connection()
    {
    }

public:
    uint32_t GetId() const
    {
        return id_;
    }
    void ConnectToClient(uint32_t uid = 0)
    {
        if (ownerType_ == Owner::Server)
        {
            if (socket_.is_open())
            {
                id_ = uid;
            }
        }
        else
        {
            std::cerr << "Can't connect client to client" << std::endl;
        }
    }
    bool ConnectToServer(const boost::asio::ip::udp::resolver::results_type &endpoints)
    {
        if (ownerType_ == Owner::Client)
        {
            boost::asio::async_connect(
                socket_, endpoints,
                [this](std::error_code ec, boost::asio::ip::udp::endpoint endpoint) {
                    if (!ec)
                    {
                        std::cout << "[CLIENT] Connected to server: "
                                  << endpoint.address().to_string() << std::endl;
                        GetHeader();
                    }
                    else
                    {
                        std::cout << "[CLIENT] Connect Fail.\n";
                        socket_.close();
                    }
                });
        }
        else
        {
            std::cerr << "Can't connect server to server" << std::endl;
        }
    }
    bool Disconnect()
    {
        if (IsConnected())
        {
            boost::asio::post(ioContext_, [this]() { socket_.close(); });
        }
    }
    bool IsConnected() const
    {
        return socket_.is_open();
    }

    bool SendPacket(const Packet<T> &packet)
    {
        if (IsConnected())
        {
            boost::asio::post(ioContext_, [this, packet]() {
                bool isWritingPacket = !packetsOutQueue_.empty();
                packetsOutQueue_.PushBack(packet);
                if (!isWritingPacket)
                {
                    SendHeader();
                }
            });
            return true;
        }
        return false;
    }

private:
    void SendHeader()
    {
        boost::asio::async_write(
            socket_, boost::asio::buffer(&packetsOutQueue_.Front().header, sizeof(PacketHeader<T>)),
            [this](std::error_code ec, std::size_t length) {
                if (!ec)
                {
                    if (packetsOutQueue_.Front().body.size() > 0)
                    {
                        SendBody();
                    }
                    else
                    {
                        packetsOutQueue_.PopFront();
                        if (!packetsOutQueue_.empty())
                        {
                            SendHeader();
                        }
                    }
                }
                else
                {
                    std::cout << "[" << id_ << "] Send Header Fail.\n";
                    socket_.close();
                }
            });
    }
    void SendBody()
    {
        boost::asio::async_write(
            socket_,
            boost::asio::buffer(
                packetsOutQueue_.Front().body.data(), packetsOutQueue_.Front().body.size()),
            [this](std::error_code ec, std::size_t length) {
                if (!ec)
                {
                    packetsOutQueue_.PopFront();
                    if (!packetsOutQueue_.empty())
                    {
                        SendHeader();
                    }
                }
                else
                {
                    std::cout << "[" << id_ << "] Send Body Fail.\n";
                    socket_.close();
                }
            });
    }

    void GetHeader()
    {
        boost::asio::async_read(
            socket_, boost::asio::buffer(&recvBuffer_.header, sizeof(PacketHeader<T>)),
            [this](std::error_code ec, std::size_t length) {
                if (!ec)
                {
                    if (recvBuffer_.header.size > 0)
                    {
                        recvBuffer_.body.resize(recvBuffer_.header.size);
                        GetBody();
                    }
                    else
                    {
                        AddToIncomingPackageQueue();
                    }
                }
                else
                {
                    std::cout << "[" << id_ << "] Get Header Fail.\n";
                    socket_.close();
                }
            });
    }
    void GetBody()
    {
        boost::asio::async_read(
            socket_, boost::asio::buffer(recvBuffer_.body.data(), recvBuffer_.body.size()),
            [this](std::error_code ec, std::size_t length) {
                if (!ec)
                {
                    AddToIncomingPackageQueue();
                }
                else
                {
                    std::cout << "[" << id_ << "] Get Body Fail.\n";
                    socket_.close();
                }
            });
    }
    void AddToIncomingPackageQueue()
    {
        if (ownerType_ == Owner::Server)
        {
            packetsInQueue_.PushBack({this->shared_from_this(), recvBuffer_});
        }
        else
        {
            packetsInQueue_.PushBack({nullptr, recvBuffer_});
        }
        GetHeader();
    }

protected:
    boost::asio::ip::udp::socket socket_;
    boost::asio::io_context &ioContext_;
    PacketsQueue<Packet<T>> packetsOutQueue_;
    PacketsQueue<Packet<T>> &packetsInQueue_;
    Owner ownerType_ = Owner::Server;
    uint32_t id_     = 0;
    Packet<T> recvBuffer_;
};
};  // namespace Network

#endif /* !CONNECTION_HPP_ */
