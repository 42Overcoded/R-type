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
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include "Packet.hpp"
#include "PacketsQueue.hpp"
#include "Protocol.hpp"
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
        Disconnect();
    }

public:
    uint32_t GetId() const
    {
        return id_;
    }

    void ConnectToClient(boost::asio::ip::udp::endpoint remoteEndpoint, uint32_t uid = 0)
    {
        if (ownerType_ == Owner::Server)
        {
            if (socket_.is_open() && !isConnected)
            {
                std::cout << "Connecting to client" << std::endl;
                id_             = uid;
                remoteEndpoint_ = remoteEndpoint;
                socket_.async_connect(remoteEndpoint_, [this](std::error_code ec) {
                    if (!ec)
                    {
                        std::cout << "Connected to client" << std::endl;
                        Packet<T> acceptPacket;
                        acceptPacket.header.flag = T::ClientAccepted;
                        SendPacket(acceptPacket);
                        std::cout << "accept client" << std::endl;
                        Packet<T> idPacket;
                        idPacket.header.flag = T::ClientAssignID;
                        idPacket << id_;
                        SendPacket(idPacket);
                        std::cout << "assign client" << std::endl;
                        isConnected = true;
                        GetHeader();
                    }
                    else
                    {
                        std::cerr << "[" << id_ << "] Connect to client fail. (" << ec.message()
                                  << ")" << std::endl;
                        socket_.close();
                    }
                });
            }
        }
        else
        {
            std::cerr << "Can't connect client to client" << std::endl;
        }
    }

    void ConnectToServer(boost::asio::ip::udp::resolver::results_type &endpoints)
    {
        if (ownerType_ == Owner::Client && !isConnected)
        {
            std::cout << "Connecting to server" << std::endl;
            remoteEndpoint_ = *endpoints.begin();
            socket_.open(remoteEndpoint_.protocol());
            socket_.async_connect(remoteEndpoint_, [this](std::error_code ec) {
                if (!ec)
                {
                    Packet<T> packet;
                    packet.header.flag = T::ServerConnect;
                    SendPacket(packet);
                }
                else
                {
                    std::cerr << "[" << id_ << "] Connect to server fail. (" << ec.message()
                              << ")" << std::endl;
                    socket_.close();
                }
            });
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
            boost::asio::post(ioContext_, [this]() {
                if (socket_.is_open())
                    socket_.close();
            });
            isConnected = false;
        }
    }

    bool IsConnected() const
    {
        return socket_.is_open() && isConnected;
    }

    bool SendPacket(const Packet<T> &packet)
    {
        if (socket_.is_open())
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

protected:
    void SendHeader()
    {
        socket_.async_send(
            boost::asio::buffer(&packetsOutQueue_.Front().header, sizeof(PacketHeader<T>)),
            [this](std::error_code ec, std::size_t length) {
                if (!ec)
                {
                    std::cout << "Send Packet: size = " << packetsOutQueue_.Front().header.size
                              << std::endl;
                    if (packetsOutQueue_.Front().header.size > sizeof(PacketHeader<T>) &&
                        packetsOutQueue_.Front().body.size() > 0)
                    {
                        SendBody();
                    }
                    else
                    {
                        if (ownerType_ == Owner::Client &&
                            packetsOutQueue_.Front().header.flag == T::ServerConnect)
                        {
                            socket_.async_connect(boost::asio::ip::udp::endpoint(), [this](std::error_code ec) {
                                if (!ec)
                                {
                                    std::cout << "Connection opened for server" << std::endl;
                                    isConnected = true;
                                    GetHeader();
                                }
                                else
                                {
                                    std::cerr << "[" << id_ << "] Connect to server fail. (" << ec.message()
                                              << ")" << std::endl;
                                    socket_.close();
                                }
                            });
                        }
                        packetsOutQueue_.PopFront();
                        if (!packetsOutQueue_.IsEmpty())
                        {
                            SendHeader();
                        }
                    }
                }
                else
                {
                    std::cerr << "[" << id_ << "] Send Header Fail. (" << ec.message() << ")"
                              << std::endl;
                    socket_.close();
                }
            });
    }

    void SendBody()
    {
        socket_.async_send(
            boost::asio::buffer(
                packetsOutQueue_.Front().body.data(), packetsOutQueue_.Front().body.size()),
            [this](std::error_code ec, std::size_t length) {
                if (!ec)
                {
                    std::cout << "Send body" << std::endl;
                    packetsOutQueue_.PopFront();
                    if (!packetsOutQueue_.IsEmpty())
                    {
                        SendHeader();
                    }
                }
                else
                {
                    std::cerr << "[" << id_ << "] Send Body Fail. (" << ec.message() << ")"
                              << std::endl;
                    socket_.close();
                }
            });
    }

    void GetHeader()
    {
        socket_.async_receive_from(
            boost::asio::buffer(&recvBuffer_.header, sizeof(PacketHeader<T>)), remoteEndpoint_,
            [this](std::error_code ec, std::size_t length) {
                if (!ec)
                {
                    // std::cout << "Get Packet: size = " << recvBuffer_.header.size << std::endl;
                    if (recvBuffer_.header.size > 0)
                    {
                        if (recvBuffer_.header.size > MaxPacketSize)
                        {
                            std::cerr << "Packet size is too big" << std::endl;
                            recvBuffer_.header.size = 0;
                            GetHeader();
                            return;
                        }
                        if (ownerType_ == Owner::Client &&
                            recvBuffer_.header.flag == T::ClientAccepted)
                        {
                            socket_.connect(remoteEndpoint_);
                        }
                        recvBuffer_.body.resize(recvBuffer_.header.size - sizeof(PacketHeader<T>));
                        GetBody();
                    }
                    else
                    {
                        AddToIncomingPackageQueue();
                    }
                }
                else
                {
                    std::cerr << "remote endpoint: " << remoteEndpoint_.address().to_string() << " port " << remoteEndpoint_.port() << std::endl;
                    std::cerr << "[" << id_ << "] Get Header Fail. (" << ec.message() << ")"
                              << std::endl;
                    socket_.close();
                }
            });
    }

    void GetBody()
    {
        socket_.async_receive_from(
            boost::asio::buffer(recvBuffer_.body, recvBuffer_.body.size()), remoteEndpoint_,
            [this](std::error_code ec, std::size_t length) {
                if (!ec)
                {
                    AddToIncomingPackageQueue();
                }
                else
                {
                    std::cerr << "[" << id_ << "] Get Body Fail. (" << ec.message() << ")"
                              << std::endl;
                    socket_.close();
                }
            });
    }

    bool ManageConnectionPacket()
    {
        if (ownerType_ == Owner::Server)
        {
            Packet<T> packet;

            switch (recvBuffer_.header.flag)
            {
            case T::ServerGetPing:
                std::cout << "Server Ping" << std::endl;
                packet.header.flag = T::ClientSendPing;
                SendPacket(packet);
                return true;
                ;
            default: break;
            }
        }
        else
        {
            switch (recvBuffer_.header.flag)
            {
            case T::ClientAccepted:
                std::cout << "Server Accept" << std::endl;
                socket_.connect(remoteEndpoint_);
                isConnected = true;
                return true;
                ;
            case T::ClientDenied:
                std::cout << "Server Deny" << std::endl;
                socket_.close();
                return true;
                ;
            case T::ClientSendPing: std::cout << "Server Ping" << std::endl; break;
            default: break;
            }
        }
        return false;
    }

    void AddToIncomingPackageQueue()
    {
        if (ManageConnectionPacket())
        {
            GetHeader();
            return;
        }
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
    bool isConnected = false;
    boost::asio::ip::udp::endpoint remoteEndpoint_;
};
};  // namespace Network

#endif /* !CONNECTION_HPP_ */
