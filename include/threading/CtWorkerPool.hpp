/*
MIT License

Copyright (c) 2024 Mouzenidis Panagiotis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file CtWorkerPool.hpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTWORKERPOOL_HPP_
#define INCLUDE_CTWORKERPOOL_HPP_

#include "definitions.hpp"
#include "threading/CtWorker.hpp"
#include "utils/CtTask.hpp"

#include <queue>
#include <atomic>
#include <mutex>
#include <functional>

/**
 * @class CtWorkerPool
 * @brief Manages a pool of worker threads for executing tasks concurrently.
 */
class CtWorkerPool {
public:
    /**
     * @brief Constructor for CtWorkerPool.
     * @param nworkers The number of worker threads in the pool.
     */
    EXPORTED_API CtWorkerPool(uint32_t nworkers);

    /**
     * @brief Destructor for CtWorkerPool.
     */
    EXPORTED_API ~CtWorkerPool();

    /**
     * @brief Add a task to the worker pool.
     * @param task The task to be added to the pool.
     */
    EXPORTED_API void addTask(CtTask& task);

    /**
     * @brief Add a task function to the worker pool.
     * 
     * @param func The task function to be added to the pool.
     * @param fargs The arguments of the task function.
     */
    template <typename F, typename... FArgs>
    EXPORTED_API void addTask(F&& func, FArgs&&... fargs);

    /**
     * @brief Wait for all worker threads to finish their tasks.
     */
    EXPORTED_API void join();

private:
    /**
     * @brief Main function running by task assigner worker.
     */
    void taskAssignerFunc();

    /**
     * @brief Assign a task to a specified worker.
     * @param idx The index of the worker to which the task is assigned.
     * @return True if a task was successfully assigned, false otherwise.
     */
    void assignTask(uint32_t idx);

    /**
     * @brief Free resources and clear the worker pool.
     */
    void free();

private:
    uint32_t m_nworkers; ///< Number of worker threads in the pool.
    std::vector<std::unique_ptr<CtWorker>> m_workers; ///< Worker thread instances.
    std::queue<CtTask> m_tasks; ///< Queue of tasks to be executed.
    std::queue<uint32_t> m_available_workers_idxs; ///< Queue of available worker indices.
    std::mutex m_mtx_control; ///< Mutex for controlling access to shared resources.
    std::atomic<uint32_t> m_active_tasks; ///< Number of active tasks that are currently running.
    std::atomic<uint32_t> m_queued_tasks; ///< Number of queued tasks.
    CtWorker m_taskAssigner; ///< This worker is a task assigner, assigns active tasks to available workers.
};

template <typename F, typename... FArgs>
void CtWorkerPool::addTask(F&& func, FArgs&&... fargs) {
    CtTask s_task;
    s_task.setTaskFunc(std::bind(std::forward<F>(func), std::get<FArgs>(fargs)...));
    addTask(s_task);
};

#endif //INCLUDE_CTWORKERPOOL_HPP_
