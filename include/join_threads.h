#ifndef JOIN_THREADS_POOL_
#define JOIN_THREADS_POOL_

#include <thread>
#include <vector>

class JoinThreads {
private:
    std::vector<std::thread>& threads;
public:
    explicit JoinThreads(std::vector<std::thread>& threads_);
    ~JoinThreads();
};

#endif