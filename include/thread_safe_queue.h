#ifndef THREAD_SAFE_QUEUE_H_
#define THREAD_SAFE_QUEUE_H_

#include <mutex>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    /* data */
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
    
public:
 ThreadSafeQueue(/* args */){}
 ~ThreadSafeQueue(){}
 void push(T new_value) {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
 }

 void wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();});
    value = std::move(data_queue.front());
    data_queue.pop();
 }
};


#endif