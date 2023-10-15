/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Packet
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <ostream>
#include <vector>

namespace Network {

template <typename T>
class Connection;

/**
 * @brief Packet header send at the beginning of each packet
 *
 * @tparam T
 */
template <typename T>
struct PacketHeader
{
    T flag{};
    uint32_t size = 0;
};

/**
 * @brief Packet send through the network
 *
 * @tparam T
 */
template <typename T>
struct Packet
{
    PacketHeader<T> header{};
    std::vector<uint8_t> body;

    /**
     * @brief Get the size of the entire packet in bytes
     *
     * @return size_t
     */
    size_t size() const
    {
        return sizeof(PacketHeader<T>) + body.size();
    }

    /**
     * @brief Display the packet in a human readable format
     *
     * @param os
     * @param packet
     * @return std::ostream&
     */
    friend std::ostream &operator<<(std::ostream &os, const Packet<T> &packet)
    {
        os << "PACKET ID: " << packet.header.flag << " SIZE: " << packet.header.size << " BODY: ";
        return os;
    }

    /**
     * @brief Push data into the packet
     *
     * @tparam DataType
     * @param data
     * @return Packet<T>&
     */
    template <typename DataType>
    friend Packet<T> &operator<<(Packet<T> &packet, const DataType &data)
    {
        static_assert(
            std::is_standard_layout<DataType>::value,
            "Data is too complex to be pushed into vector");

        size_t startIndex = packet.body.size();
        packet.body.resize(packet.body.size() + sizeof(DataType));
        std::memcpy(packet.body.data() + startIndex, &data, sizeof(DataType));
        packet.header.size = packet.size();
        return packet;
    }

    /**
     * @brief Pop data from the packet
     *
     * @tparam DataType
     * @param data
     * @return Packet<T>&
     */
    template <typename DataType>
    friend Packet<T> &operator>>(Packet<T> &packet, DataType &data)
    {
        static_assert(
            std::is_standard_layout<DataType>::value,
            "Data is too complex to be pushed into vector");

        size_t startIndex = packet.body.size() - sizeof(DataType);
        std::memcpy(&data, packet.body.data() + startIndex, sizeof(DataType));
        packet.body.resize(startIndex);
        packet.header.size = packet.size();
        return packet;
    }
};

template <typename T>
struct OwnedPacket
{
    std::shared_ptr<Connection<T>> remote = nullptr;
    Packet<T> packet;

    friend std::ostream &operator<<(std::ostream &os, const OwnedPacket<T> &opacket)
    {
        os << opacket.packet;
        return os;
    }
};

}  // namespace Network

#endif /* !PACKET_HPP_ */
