#include "thread_pool.h"
#include <iostream>
#include <string>

int first() {
    std::cout << "hello world!\n";
    return 1;
}

int second() {
    std::cout << "hello thread_pool\n";
    return 2;
}

int main(int argc, char **argv) {
    ThreadPool pool;
    std::future<int> a = pool.submit(first);
    std::future<int> b = pool.submit(second);
    int c = a.get() + b.get();
    std::cout << c << std::endl;
    return 0;
}