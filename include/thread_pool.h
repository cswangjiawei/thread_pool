#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <atomic>
#include <functional>
#include <thread>
#include <vector>
#include "thread_safe_queue.h"

class ThreadPool {
private:
    /* data */
    std::atomic_bool done;
    ThreadSafeQueue<std::function<void()> > work_queue;
    std::vector<std::thread> threads;

    void worker_thread();

public:
    ThreadPool(/* args */);
    ~ThreadPool();

    template<typename FunctionType>
    void submit(FunctionType f) {
    work_queue.push(std::function<void()>(f));
    }
};



#endif