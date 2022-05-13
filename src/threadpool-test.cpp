#include "threadpool.h"
#include <iostream>

int main() {
    ThreadPool pool { 8 };

    pool.add_task([] {
        std::cout << "Hello from " << std::this_thread::get_id() << std::endl;
    });
}
