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
        std::scoped_lock lock(mutexQueue);
        return localQueue.front();
    }

    const T &Back()
    {
        std::scoped_lock lock(mutexQueue);
        return localQueue.back();
    }

    T PopFront()
    {
        std::scoped_lock lock(mutexQueue);
        auto t = std::move(localQueue.front());
        localQueue.pop_front();
        return t;
    }

    T PopBack()
    {
        std::scoped_lock lock(mutexQueue);
        auto t = std::move(localQueue.back());
        localQueue.pop_back();
        return t;
    }

    void PushFront(const T &item)
    {
        std::scoped_lock lock(mutexQueue);
        localQueue.emplace_front(std::move(item));
    }

    void PushBack(const T &item)
    {
        std::scoped_lock lock(mutexQueue);
        localQueue.emplace_back(std::move(item));
    }

    bool IsEmpty()
    {
        std::scoped_lock lock(mutexQueue);
        return localQueue.empty();
    }

    size_t GetSize()
    {
        std::scoped_lock lock(mutexQueue);
        return localQueue.size();
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
        std::scoped_lock lock(mutexQueue);
        localQueue.clear();
    }

protected:
    std::mutex mutexQueue;
    std::deque<T> localQueue;
    std::condition_variable cvBlocking;
    std::mutex muxBlocking;
};
};  // namespace Network

#endif /* !PACKETSQUEUE_HPP_ */
