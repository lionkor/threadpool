#pragma once

#include <cstdint>
#include <cstddef>
#include <functional>

class ThreadPool {
public:
    using Task = std::function<void()>;

    /// constructs the threadpool with n_threads threads
    explicit ThreadPool(size_t n_threads);
    /// blocks the destruction until all tasks are finished
    ~ThreadPool();

    /// adds a task to be executed
    void add_task(Task task);

private:
};
