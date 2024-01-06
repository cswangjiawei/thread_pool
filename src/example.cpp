#include "thread_pool.h"
#include <iostream>
#include <string>
#include <numeric>
#include <vector>

int first() {
    std::cout << "hello world!\n";
    return 1;
}

int second() {
    std::cout << "hello thread_pool\n";
    return 2;
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);
    std::cout<<"length:"<<length<<std::endl;
    if (!length) {
        return init;
    }
    unsigned long const block_size = 5;
    unsigned long const num_blocks = (length + block_size - 1) / block_size;
    std::vector<std::future<T> > futures(num_blocks - 1);
    
    ThreadPool pool;
    Iterator block_start = first;
    for(unsigned long i = 0; i < (num_blocks - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        futures[i] = pool.submit([=] () -> int {
           return std::accumulate(block_start, block_end, T());
        });
        block_start = block_end;
    }

    T last_result =  std::accumulate(block_start, last, T());
    T result = init;
    for (unsigned long i = 0; i < (num_blocks - 1); ++i) {
        result += futures[i].get();
    }
    result += last_result;
    std::cout<<"result:"<<result<<std::endl;
    return result;
}

int main(int argc, char **argv) {
    // ThreadPool pool;
    // std::future<int> a = pool.submit(first);
    // std::future<int> b = pool.submit(second);
    // int c = a.get() + b.get();
    // std::cout << c << std::endl;
    std::vector<unsigned long> vec = {1, 2, 3, 4, 5, 7, 8, 9, 10};
    int init = 0;
    parallel_accumulate(vec.begin(), vec.end(), init);
    
    return 0;
}