/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** INetworkServer
*/

#ifndef INETWORKSERVER_HPP_
#define INETWORKSERVER_HPP_
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <deque>
#include <iostream>
#include <memory>
#include "Connection.hpp"
#include "Packet.hpp"
#include "PacketsQueue.hpp"
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/udp.hpp"
#include "boost/asio/write.hpp"

namespace Network {

template <typename T>
class Packet;

template <typename T>
class INetworkServer
{
private:
    class ClientsManager
    {
    public:
        ClientsManager(boost::asio::io_context &ioContext, boost::asio::ip::udp::socket &socket, PacketsQueue<OwnedPacket<T>> &packetsQueue, std::deque<std::shared_ptr<Connection<T>>> &clients) : socket_(socket), ioContext_(ioContext), packetsInQueue_(packetsQueue), clients_(clients){};
        ~ClientsManager() = default;

    protected:
        void GetPacket()
        {
            socket_.async_receive_from(
                boost::asio::buffer(&recvBuffer_.header, sizeof(PacketHeader<T>)), remoteEndpoint_,
                [this](std::error_code ec, std::size_t length) {
                    if (!ec)
                    {
                        if (recvBuffer_.header.size == 0)
                        {
                            ManageConnectionPacket();
                        } else {
                            std::cerr << "Packet size is not 0" << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "[" << id_ << "] Get Header Fail.\n";
                        socket_.close();
                    }
                });
        }

        void ManageConnectionPacket()
        {
            switch (recvBuffer_.header.flag)
            {
            case T::ServerConnect:
                std::cout << "Server Connect" << std::endl;
                boost::asio::ip::udp::socket newSocket(ioContext_, remoteEndpoint_.protocol(), 0);
                std::shared_ptr<Connection<T>> newClient =
                    std::make_shared<Connection<T>>(Connection<T>::Owner::Server, ioContext_,
                    newSocket, packetsInQueue_);
                newClient->ConnectToClient(remoteEndpoint_);
                clients_.push_back(newClient);
            }
            GetPacket();
        }

    private:
        boost::asio::ip::udp::socket &socket_;
        boost::asio::io_context &ioContext_;
        PacketsQueue<OwnedPacket<T>> &packetsInQueue_;
        uint32_t id_ = 0;
        Packet<T> recvBuffer_;
        boost::asio::ip::udp::endpoint remoteEndpoint_;
        std::deque<std::shared_ptr<Connection<T>>> &clients_;
    };

public:
    INetworkServer(uint16_t port)
        : socket_(
              ioContext_,
              boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
              clientsManager_(ioContext_, socket_, packetsInQueue_, clients_){};

    virtual ~INetworkServer()
    {
        Stop();
    };

public:
    bool Start()
    {
        try
        {
            clientsManager_.GetPacket();
            threadContext_ = std::thread([this]() { ioContext_.run(); });
        }
        catch (const std::exception &e)
        {
            std::cerr << "[SERVER] Exception: " << e.what() << std::endl;
            return false;
        }
        std::cout << "[SERVER] Started" << std::endl;
        return true;
    };

    void Stop()
    {
        ioContext_.stop();
        if (threadContext_.joinable())
            threadContext_.join();
        std::cout << "[SERVER] Stopped" << std::endl;
    };

    void SendToClient(const Packet<T> &packet, const std::shared_ptr<Connection<T>> client)
    {
        if (client && client->IsConnected())
        {
            client->Send(packet);
        }
        else
        {
            OnClientDisconnect(client);
            client.reset();
            clients_.erase(std::remove(clients_.begin(), clients_.end(), client), clients_.end());
        }
    };

    void SendToAllClients(const Packet<T> &packet)
    {
        for (auto &client : clients_)
        {
            SendToClient(packet, client);
        };
    };

    void UpdateServer(size_t maxPacketsNbr = -1)
    {
        size_t packetCount = 0;
        while (packetCount < maxPacketsNbr && !packetsInQueue_.IsEmpty())
        {
            auto packet = packetsInQueue_.PopFront();
            OnReceive(packet.remote, packet.packet);
            packetCount++;
        }
    }

protected:
    virtual bool OnClientConnect(std::shared_ptr<Connection<T>> client)
    {
        return false;
    };

    virtual void OnClientDisconnect(std::shared_ptr<Connection<T>> client){

    };

    virtual void OnReceive(std::shared_ptr<Connection<T>> client, Packet<T> &packet){

    };

protected:
    PacketsQueue<OwnedPacket<T>> packetsInQueue_;
    std::deque<std::shared_ptr<Connection<T>>> clients_;
    boost::asio::io_context ioContext_;
    std::thread threadContext_;
    uint32_t nIDCounter_ = 10000;
    boost::asio::ip::udp::socket socket_;
    ClientsManager clientsManager_;
};
};  // namespace Network

#endif /* !INETWORKSERVER_HPP_ */
