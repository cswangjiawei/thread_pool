#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <atomic>
#include <functional>
#include <thread>
#include <vector>
#include <future>
#include "thread_safe_queue.h"
#include "join_threads.h"

class ThreadPool {
private:
    /* data */
    std::atomic_bool done;
    ThreadSafeQueue<std::packaged_task<int() > > work_queue;
    std::vector<std::thread> threads;
    JoinThreads joiner;

    void worker_thread();

public:
    ThreadPool(/* args */);
    ~ThreadPool();

    template<typename FunctionType>
    std::future<int> submit(FunctionType f) {
        std::packaged_task<decltype(f())() > task(f);
        std::future<int> res(task.get_future());
        work_queue.push(std::move(task));
        return res;
    }
};



#endif