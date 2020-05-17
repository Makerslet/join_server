#ifndef COMMANDS_QUEUE_H
#define COMMANDS_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

/**
 * @brief Класс многопоточной неограниченной очереди,
 * обеспечивающей ожидание и уведомление читающих потоков
 */
template<typename T>
class queue_mt
{
public:
    /**
     * @brief Конструктор
     */
    queue_mt()
    {
        _is_running.store(true);
    }

    /**
     * @brief Положить элемен в очередь
     */
    void push(T&& value)
    {
        std::unique_lock<std::mutex> lock(_control_mutex);
        _cmds_queue.push(std::move(value));
        lock.unlock();
        _cond_var.notify_one();
    }

    /**
     * @brief Извлечь элемент из очереди
     */
    T pop()
    {
        std::unique_lock<std::mutex> lock(_control_mutex);
        _cond_var.wait(lock, [this](){return (!_cmds_queue.empty() || !_is_running);});

        if(!_is_running.load())
            return T();

        auto value(std::move(_cmds_queue.front()));
        _cmds_queue.pop();

        return value;
    }

    void shutdown()
    {
        _is_running.store(false);
        _cond_var.notify_all();
    }

    bool is_running() const
    {
        return _is_running.load();
    }

private:
    std::condition_variable _cond_var;
    std::mutex _control_mutex;
    std::queue<T> _cmds_queue;
    std::atomic<bool> _is_running;
};

#endif // COMMANDS_QUEUE_H
