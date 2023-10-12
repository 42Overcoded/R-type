/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** PacketsQueue
*/

#ifndef PACKETSQUEUE_HPP_
#define PACKETSQUEUE_HPP_
#include <deque>
#include <mutex>


namespace Network {

/**
 * @brief Thread safe queue of packets
 * 
 * @tparam T 
 */
template <typename T>
class PacketsQueue
{
public:
    PacketsQueue()                        = default;
    PacketsQueue(const PacketsQueue<T> &) = delete;

    const T &front()
    {
        std::scoped_lock lock(muxQueue);
        return deqQueue.front();
    }

    const T &back()
    {
        std::scoped_lock lock(muxQueue);
        return deqQueue.back();
    }

    T pop_front()
    {
        std::scoped_lock lock(muxQueue);
        auto t = std::move(deqQueue.front());
        deqQueue.pop_front();
        return t;
    }

    T pop_back()
    {
        std::scoped_lock lock(muxQueue);
        auto t = std::move(deqQueue.back());
        deqQueue.pop_back();
        return t;
    }

    void push_front(const T &item)
    {
        std::scoped_lock lock(muxQueue);
        deqQueue.emplace_front(std::move(item));
    }

    void push_back(const T &item)
    {
        std::scoped_lock lock(muxQueue);
        deqQueue.emplace_back(std::move(item));
    }

protected:
    std::mutex muxQueue;
    std::deque<T> deqQueue;
};
};  // namespace Network

#endif /* !PACKETSQUEUE_HPP_ */
