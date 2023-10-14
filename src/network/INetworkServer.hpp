/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** INetworkServer
*/

#ifndef INETWORKSERVER_HPP_
#define INETWORKSERVER_HPP_
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <deque>
#include <iostream>
#include <memory>
#include "Packet.hpp"
#include "boost/asio/io_context.hpp"
#include "PacketsQueue.hpp"

namespace Network {

template <typename T>
class Connection;

template <typename T>
class Packet;

template <typename T>
class INetworkServer
{
public:
    INetworkServer(uint16_t port)
        : socket_(ioContext_, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)){};

    virtual ~INetworkServer()
    {
        Stop();
    };

public:
    bool Start()
    {
        try
        {
            WaitForClientConnection();
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

    bool Stop()
    {
        ioContext_.stop();
        if (threadContext_.joinable())
            threadContext_.join();
        std::cout << "[SERVER] Stopped" << std::endl;
    };

    void WaitForClientConnection()
    {
        std::cout << "[SERVER] New Connection" << std::endl;
        std::shared_ptr<Connection<T>> newClient = std::make_shared<Connection<T>>(
            Connection<T>::OwnerType::Server, ioContext_, socket_, packetsInQueue_);
        if (OnClientConnect(newClient))
        {
            clients_.push_back(std::move(newClient));
            clients_.back()->ConnectToClient(nIDCounter_++);
            std::cout << "[" << clients_.back()->GetID() << "] Connection Approved" << std::endl;
        }
        else
        {
            std::cout << "[-----] Connection Denied" << std::endl;
        }
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
        while (packetCount < maxPacketsNbr && !packetsInQueue_.empty())
        {
            auto packet = packetsInQueue_.pop_front();
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
};
};  // namespace Network

#endif /* !INETWORKSERVER_HPP_ */
