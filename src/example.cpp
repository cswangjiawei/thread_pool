#include "thread_pool.h"
#include <iostream>
#include <string>

void first() {
    std::cout << "hello world!" << std::endl;
}

void second() {
    std::cout << "hello thread_pool" << std::endl;
}

int main(int argc, char **argv) {
    ThreadPool pool;
    pool.submit(first);
    pool.submit(second);
    return 0;
}