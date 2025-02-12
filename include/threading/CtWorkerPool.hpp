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
 * @brief CtWorkerPool class header file.
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTWORKERPOOL_HPP_
#define INCLUDE_CTWORKERPOOL_HPP_

#include "core.hpp"

#include "threading/CtWorker.hpp"
#include "threading/CtThread.hpp"
#include "threading/CtTask.hpp"

#include <functional>

/**
 * @class CtWorkerPool
 * @brief Manages a pool of worker threads for executing tasks concurrently.
 * 
 * @ref FR-005-004-001
 * @ref FR-005-004-002
 * 
 * @details
 * The CtWorkerPool class provides a mechanism for managing a pool of worker threads that can execute tasks concurrently.
 * The class is thread-safe and can be used in multi-threaded environments.
 * 
 * @code {.cpp}
 * // create a pool with 4 worker threads
 * CtWorkerPool pool(4);
 * // add tasks to the pool
 * // add a lambda function
 * pool.addTask([](){ std::cout << "Hello from worker thread!" << std::endl; });
 * // add a function with arguments
 * pool.addTask(func, arg1, arg2);
 * // add a CtTask object
 * pool.addTask(task);
 * // wait for all worker threads to finish
 * pool.join();
 * @endcode
 * 
 */
class CtWorkerPool : private CtThread {
public:
    /**
     * @brief Constructor for CtWorkerPool.
     * 
     * @ref FR-005-004-003
     * 
     * @param nworkers The number of worker threads in the pool.
     */
    EXPORTED_API explicit CtWorkerPool(CtUInt32 nworkers);

    /**
     * @brief Destructor for CtWorkerPool.
     * 
     * @ref FR-005-004-004
     * @ref FR-005-004-005
     * 
     */
    EXPORTED_API ~CtWorkerPool();

    /**
     * @brief Add a task to the worker pool.
     * 
     * @ref FR-005-004-006
     * 
     * @param task The task to be added to the pool.
     */
    EXPORTED_API void addTask(const CtTask& task);

    /**
     * @brief Add a task function to the worker pool.
     * 
     * @ref FR-005-004-006
     * 
     * @param func The task function to be added to the pool.
     * @param fargs The arguments of the task function.
     */
    template <typename F, typename... FArgs>
    EXPORTED_API void addTask(const F&& func, FArgs&&... fargs);

    /**
     * @brief Wait for all worker threads to finish their tasks.
     * 
     * @ref FR-005-004-007
     * 
     */
    EXPORTED_API void join() override;

private:
    /**
     * @brief Assign a task to a specified worker.
     * 
     * @ref FR-005-004-008
     * 
     * @param idx The index of the worker to which the task is assigned.
     * @return True if a task was successfully assigned, CT_FALSE otherwise.
     */
    void assignTask(CtUInt32 idx);

    /**
     * @brief Free resources and clear the worker pool.
     * 
     * @ref FR-005-004-004
     * 
     */
    void free();

    /**
     * @brief Main loop for the worker pool.
     * 
     * @ref FR-005-004-008
     * @ref FR-005-004-009
     * 
     */
    void loop() override;

private:
    CtUInt32 m_nworkers;                             /*!< Number of worker threads in the pool. */
    CtVector<std::unique_ptr<CtWorker>> m_workers;   /*!< Worker thread instances. */
    CtQueue<CtTask> m_tasks;                         /*!< Queue of tasks to be executed. */
    CtQueue<CtUInt32> m_available_workers_idxs;      /*!< Queue of available worker indices. */
    CtMutex m_mtx_control;                           /*!< Mutex for controlling access to shared resources. */
    CtAtomic<CtUInt32> m_active_tasks;               /*!< Number of active tasks that are currently running. */
    CtAtomic<CtUInt32> m_queued_tasks;               /*!< Number of queued tasks. */
    CtWorker m_taskAssigner;                         /*!< This worker is a task assigner, assigns active tasks to available workers. */
};

template <typename F, typename... FArgs>
void CtWorkerPool::addTask(const F&& func, FArgs&&... fargs) {
    CtTask s_task;
    s_task.setTaskFunc(std::bind(func, std::forward<FArgs>(fargs)...));
    addTask(s_task);
};

#endif //INCLUDE_CTWORKERPOOL_HPP_
