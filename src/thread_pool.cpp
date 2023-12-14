#include "thread_pool.h"

ThreadPool::ThreadPool():done(false) {
    unsigned const thread_count = std::thread::hardware_concurrency();
    try {
        for (unsigned i=0; i<thread_count; ++i) {
            threads.emplace_back(std::thread(&ThreadPool::worker_thread, this));
        }
    } catch(...) {
        done = true;
        throw;
    }
}

ThreadPool::~ThreadPool() {
    done = true;
    for (unsigned i=0; i<threads.size(); ++i) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
}

void ThreadPool::worker_thread() {
    while (!done) {
        std::function<void()> task;
        work_queue.wait_and_pop(task);
        task();
    }
    
}