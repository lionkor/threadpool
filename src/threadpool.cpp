// This source code is licensed under the
// Creative Commons Zero v1.0 Universal License
// (CC0 1.0 Universal / CC0 1.0)
// https://creativecommons.org/publicdomain/zero/1.0/legalcode

// Author: Lion Kortlepel / @lionkor / development@kortlepel.com

#include "threadpool.h"

ThreadPool::ThreadPool(size_t n_threads) {
    m_threads.reserve(n_threads);
    for (size_t i = 0; i < n_threads; ++i) {
        m_threads.emplace_back(&ThreadPool::thread_main, this);
    }
}

void ThreadPool::thread_main() {
    while (!m_shutdown) {
        // if we have tasks, we want to move the
        // first task out, remove it from the queue,
        // and then execute it
        std::unique_lock lock(m_tasks_mtx);
        // with the lock, we can now wait on it with our condition variable
        m_tasks_cnd.wait(lock);
        while (!m_tasks.empty()) {
            Task task = std::move(m_tasks.front());
            m_tasks.pop();
            lock.unlock();
            task();
            lock.lock();
        }
    }
}

ThreadPool::~ThreadPool() {
    std::unique_lock lock(m_tasks_mtx);
    while (!m_tasks.empty()) {
        lock.unlock();
        m_tasks_cnd.notify_all();
        lock.lock();
    }
    lock.unlock();
    for (auto& thread : m_threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void ThreadPool::add_task(Task task) {
    std::unique_lock lock(m_tasks_mtx);
    m_tasks.emplace(std::move(task));
    m_tasks_cnd.notify_one();
}
