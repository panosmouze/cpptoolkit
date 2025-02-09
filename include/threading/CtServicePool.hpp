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
 * @file CtServicePool.hpp
 * @brief CtServicePool class header file.
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTSERVICEPOOL_HPP_
#define INCLUDE_CTSERVICEPOOL_HPP_

#include "core.hpp"

#include "threading/CtService.hpp"
#include "threading/CtWorkerPool.hpp"
#include "threading/CtThread.hpp"
#include "time/CtTimer.hpp"
#include "threading/CtTask.hpp"

/**
 * @class CtServicePool
 * @brief A service pool for managing and executing tasks at specified intervals using a worker pool.
 * 
 * @details
 * The CtServicePool class provides a mechanism for managing and executing tasks at specified intervals using a worker pool.
 * CtService::m_slot_time is used to determine the interval at which tasks are executed. The default slot time is 10 ms.
 * You can modify the slot time using the setSlotTime() method. The class uses a worker pool to execute tasks concurrently.
 * The class is thread-safe and can be used in multi-threaded environments.
 * 
 * @code {.cpp}
 * // create a service pool with 4 worker threads
 * CtServicePool pool(4);
 * // add tasks to the pool
 * // add a lambda function
 * pool.addTask(100, [](){ std::cout << "Hello from worker thread!" << std::endl; });
 * // add a function with arguments
 * pool.addTask(100, func, arg1, arg2);
 * // start the services
 * pool.startServices();
 * // stop the services
 * pool.shutdownServices();
 * @endcode 
 */
class CtServicePool : private CtThread {
private:
    /**
     * @struct CtServicePack
     * @brief Represents a pack containing a task, an ID, and an interval for execution.
     */
    typedef struct _CtServicePack {
        CtTask task;
        CtString id;
        CtUInt32 nslots;
    } CtServicePack;

public:
    /**
     * @brief Constructor for CtServicePool.
     * @param nworkers The number of worker threads in the service pool.
     */
    EXPORTED_API explicit CtServicePool(CtUInt32 nworkers);

    /**
     * @brief Destructor for CtServicePool.
     */
    EXPORTED_API ~CtServicePool();

    /**
     * @brief Add a task to the service pool with a specified interval and an optional ID.
     * 
     * @details
     * Adding a task to the service pool with a specified interval and an optional ID.
     * The service pool automatically starts when a task is added.
     * 
     * @param nslots The interval in slots for executing the task.
     * @param id An optional ID for the task.
     * @param task The task to be added.
     */
    EXPORTED_API void addTask(CtUInt32 nslots, const CtString& id, CtTask& task);

    /**
     * @brief Add a task to the service pool with a specified interval and an optional ID.
     * 
     * @details
     * Adding a task to the service pool with a specified interval and an optional ID.
     * The service pool automatically starts when a task is added.
     * 
     * @param nslots The interval in slots for executing the task.
     * @param id An optional ID for the task.
     * @param func The task function to be added.
     * @param fargs The task function's arguments to be added.
     */
    template <typename F, typename... FArgs>
    EXPORTED_API void addTaskFunc(CtUInt32 nslots, const CtString& id, F&& func, FArgs&&... fargs);

    /**
     * @brief Remove a task from the service pool based on its ID.
     * @param id The ID of the task to be removed.
     */
    EXPORTED_API void removeTask(const CtString& id);

    /**
     * @brief Start the services provided by the service pool.
     */
    EXPORTED_API void startServices();

    /**
     * @brief Shutdown the services provided by the service pool.
     */
    EXPORTED_API void shutdownServices();

private:
    /**
     * @brief Overridden loop function from CtThread, representing the main thread logic.
     */
    void loop() override;

private:
    CtUInt32 m_nworkers;                    /*!< The number of worker threads in the service pool. */
    CtUInt32 m_slot_cnt;                    /*!< Counter for the current slot. */
    CtVector<CtServicePack> m_tasks;        /*!< Vector of tasks in the service pool. */
    CtMutex m_mtx_control;                  /*!< Mutex for controlling access to shared resources. */
    CtWorkerPool m_worker_pool;             /*!< Worker pool for executing tasks. */
    CtTimer m_timer;                        /*!< Timer for tracking time intervals. */
    CtUInt64 m_exec_time;                   /*!< Variable used for time tracking during a loop. */
};

template <typename F, typename... FArgs>
void CtServicePool::addTaskFunc(CtUInt32 nslots, const CtString& id, F&& func, FArgs&&... fargs) {
    CtTask s_task;
    s_task.setTaskFunc(std::bind(func, std::forward<FArgs>(fargs)...));
    addTask(nslots, id, s_task);
};

#endif //INCLUDE_CTSERVICEPOOL_HPP_
