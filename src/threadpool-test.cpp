#include "threadpool.h"
#include <iostream>

int main() {
    ThreadPool pool { 8 };

    pool.add_task([] {
        std::cout << "Hello, ThreadPool!" << std::endl;
    });
}
