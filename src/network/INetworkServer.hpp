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
#include <cstdint>
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
        ClientsManager(
            boost::asio::io_context &ioContext,
            std::uint32_t port,
            PacketsQueue<OwnedPacket<T>> &packetsQueue,
            std::shared_ptr<std::deque<std::shared_ptr<Connection<T>>>> clients)
            : ioContext_(ioContext), packetsInQueue_(packetsQueue), clients_(clients)
        {
            socket_ = std::make_unique<boost::asio::ip::udp::socket>(
                ioContext_, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
        };
        ~ClientsManager() = default;

        void GetPacket()
        {
            socket_->async_receive_from(
                boost::asio::buffer(&recvBuffer_.header, sizeof(PacketHeader<T>)), remoteEndpoint_,
                [this](std::error_code ec, std::size_t length) {
                    if (!ec)
                    {
                        if (recvBuffer_.header.size == 0)
                        {
                            std::cout << "[" << id_ << "] Get Header Success." << std::endl;
                            ManageConnectionPacket();
                        }
                        else
                        {
                            std::cerr << "Packet size is not 0" << std::endl;
                            GetPacket();
                        }
                    }
                    else
                    {
                        std::cout << "[" << id_ << "] Get Header Fail." << std::endl;
                        std::cerr << ec.message() << std::endl;
                        socket_->close();
                    }
                });
        }

    protected:
        void ManageConnectionPacket()
        {
            switch (recvBuffer_.header.flag)
            {
            case T::ServerConnect:
                std::cout << "Server Connect" << std::endl;

                std::shared_ptr<Connection<T>> newClient = std::make_shared<Connection<T>>(
                    Connection<T>::Owner::Server, ioContext_,
                    boost::asio::ip::udp::socket(
                        ioContext_, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)),
                    packetsInQueue_);
                if (clients_ == nullptr)
                    throw std::runtime_error("clients_ is null");
                std::cout << "New client created" << std::endl;
                newClient->ConnectToClient(remoteEndpoint_, id_++);
                clients_->push_back(newClient);
            }
            GetPacket();
        }

    private:
        std::unique_ptr<boost::asio::ip::udp::socket> socket_;
        boost::asio::io_context &ioContext_;
        PacketsQueue<OwnedPacket<T>> &packetsInQueue_;
        uint32_t id_ = 0;
        Packet<T> recvBuffer_;
        boost::asio::ip::udp::endpoint remoteEndpoint_;
        std::shared_ptr<std::deque<std::shared_ptr<Connection<T>>>> clients_;
    };

public:
    INetworkServer(uint16_t port)
    {
        clients_ = std::make_shared<std::deque<std::shared_ptr<Connection<T>>>>();
        clientsManager_ = std::make_unique<ClientsManager>(ioContext_, port, packetsInQueue_, clients_);
        std::cout << "[SERVER] Created" << std::endl;
        Start();
    };

    virtual ~INetworkServer()
    {
        Stop();
    };

public:
    bool Start()
    {
        try
        {
            clientsManager_->GetPacket();
            std::cout << "[SERVER] Starting..." << std::endl;
            threadContext_ = std::thread([this]() { ioContext_.run(); });
            std::cout << "[SERVER] Started" << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "[SERVER] Exception: " << e.what() << std::endl;
            return false;
        }
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
            clients_->erase(std::remove(clients_->begin(), clients_->end(), client), clients_->end());
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
    std::shared_ptr<std::deque<std::shared_ptr<Connection<T>>>> clients_;
    boost::asio::io_context ioContext_;
    std::thread threadContext_;
    uint32_t nIDCounter_ = 10000;
    std::unique_ptr<ClientsManager> clientsManager_;
};
};  // namespace Network

#endif /* !INETWORKSERVER_HPP_ */
