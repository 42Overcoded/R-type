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
#include "PacketsQueue.hpp"
#include "boost/asio/io_context.hpp"

namespace Network {

template <typename T>
class Packet;

template <typename T>
class PacketsQueue;

template <typename T>
class Connection : public std::enable_shared_from_this<Connection<T>>
{
public:
    Connection()
    {
    }
    virtual ~Connection()
    {
    }

public:
    bool ConnectToServer();
    bool Disconnect();
    bool IsConnected() const;

    bool Send(const Packet<T> &packet);

protected:
    boost::asio::ip::udp::socket socket_;
    boost::asio::io_context &ioContext_;
    PacketsQueue<Packet<T>> packetsOutQueue_;
    PacketsQueue<Packet<T>> &packetsInQueue_;
};
};  // namespace Network

#endif /* !CONNECTION_HPP_ */
