#include "thread_safe_queue.h"

template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue() {

}

template<typename T>
ThreadSafeQueue<T>::~ThreadSafeQueue() {

}

template<typename T>
void ThreadSafeQueue<T>::push(T new_value) {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
}

template<typename T>
void ThreadSafeQueue<T>::wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();});
    value = std::move(data_queue.front());
    data_queue.pop();
}
