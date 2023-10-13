/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** PacketsQueue
*/

#ifndef PACKETSQUEUE_HPP_
#define PACKETSQUEUE_HPP_
#include <cstddef>
#include <deque>
#include <mutex>
#include <condition_variable>


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

    const T &Front()
    {
        std::scoped_lock lock(muxQueue);
        return deqQueue.front();
    }

    const T &Back()
    {
        std::scoped_lock lock(muxQueue);
        return deqQueue.back();
    }

    T PopFront()
    {
        std::scoped_lock lock(muxQueue);
        auto t = std::move(deqQueue.front());
        deqQueue.pop_front();
        return t;
    }

    T PopBack()
    {
        std::scoped_lock lock(muxQueue);
        auto t = std::move(deqQueue.back());
        deqQueue.pop_back();
        return t;
    }

    void PushFront(const T &item)
    {
        std::scoped_lock lock(muxQueue);
        deqQueue.emplace_front(std::move(item));
    }

    void PushBack(const T &item)
    {
        std::scoped_lock lock(muxQueue);
        deqQueue.emplace_back(std::move(item));
    }

    bool IsEmpty()
    {
        std::scoped_lock lock(muxQueue);
        return deqQueue.empty();
    }

    size_t GetSize()
    {
        std::scoped_lock lock(muxQueue);
        return deqQueue.size();
    }

    void Wait()
    {
        while(IsEmpty())
        {
            std::unique_lock<std::mutex> ul(muxBlocking);
            cvBlocking.wait(ul);
        }
    }

    void Clear()
    {
        std::scoped_lock lock(muxQueue);
        deqQueue.clear();
    }

protected:
    std::mutex muxQueue;
    std::deque<T> deqQueue;
    std::condition_variable cvBlocking;
    std::mutex muxBlocking;
};
};  // namespace Network

#endif /* !PACKETSQUEUE_HPP_ */
