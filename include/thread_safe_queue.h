#ifndef THREAD_SAFE_QUEUE_H_
#define THREAD_SAFE_QUEUE_H_

#include <mutex>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue
{
private:
    /* data */
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
    
public:
    ThreadSafeQueue(/* args */);
    ~ThreadSafeQueue();
    void push(T new_value);
    void wait_and_pop(T& value);
};


#endif