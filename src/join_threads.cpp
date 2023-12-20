#include "join_threads.h"

JoinThreads::JoinThreads(std::vector<std::thread>& threads_)
    : threads(threads_) {}

JoinThreads::~JoinThreads() {
    for (unsigned i = 0; i < threads.size(); ++i) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
}