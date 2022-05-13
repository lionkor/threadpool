#pragma once

#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

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
    void thread_main();

    std::queue<Task> m_tasks;
    std::mutex m_tasks_mtx;
    std::condition_variable m_tasks_cnd;
    std::vector<std::thread> m_threads;

    bool m_shutdown { false };
};
