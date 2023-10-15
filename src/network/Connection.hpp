/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <cstddef>
#include <iostream>
#include "Packet.hpp"
#include "PacketsQueue.hpp"
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/udp.hpp"
#include "boost/asio/write.hpp"
#include <sys/types.h>

namespace Network {

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
        PacketsQueue<OwnedPacket<T>> &packetsInQueue)
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
                GetHeader();
            }
        }
        else
        {
            std::cerr << "Can't connect client to client" << std::endl;
        }
    }
    void ConnectToServer(boost::asio::ip::udp::resolver::results_type &endpoints)
    {
        if (ownerType_ == Owner::Client)
        {
            Packet<T> packet;
            packet << T::ServerConnect;
            SendPacket(packet);
            std::cout <<  "Connect to server" << std::endl;
            GetHeader();
        }
        else
        {
            std::cerr << "Can't connect server to server" << std::endl;
        }
    }
    void Disconnect()
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
                bool isWritingPacket = !packetsOutQueue_.IsEmpty();
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
        socket_.async_send(
            boost::asio::buffer(&packetsOutQueue_.Front().header, sizeof(PacketHeader<T>)),
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
                        if (!packetsOutQueue_.IsEmpty())
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
        socket_.async_send(
            boost::asio::buffer(packetsOutQueue_.Front().body.data(),
                                packetsOutQueue_.Front().body.size()),
            [this](std::error_code ec, std::size_t length) {
                if (!ec)
                {
                    packetsOutQueue_.PopFront();
                    if (!packetsOutQueue_.IsEmpty())
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
        socket_.async_receive(
            boost::asio::buffer(&recvBuffer_.header, sizeof(PacketHeader<T>)),
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
        socket_.async_receive(
            boost::asio::buffer(recvBuffer_.body.data(), recvBuffer_.body.size()),
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
    PacketsQueue<OwnedPacket<T>> &packetsInQueue_;
    Owner ownerType_ = Owner::Server;
    uint32_t id_     = 0;
    Packet<T> recvBuffer_;
};
};  // namespace Network

#endif /* !CONNECTION_HPP_ */
