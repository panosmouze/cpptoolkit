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
 * @brief 
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTSERVICEPOOL_HPP_
#define INCLUDE_CTSERVICEPOOL_HPP_

#include "definitions.hpp"
#include "CtTypes.hpp"
#include "threading/CtService.hpp"
#include "threading/CtWorkerPool.hpp"
#include "threading/CtThread.hpp"
#include "time/CtTimer.hpp"
#include "utils/CtTask.hpp"

#include <vector>
#include <mutex>

/**
 * @class CtServicePool
 * @brief A service pool for managing and executing tasks at specified intervals using a worker pool.
 */
class CtServicePool : private CtThread {
private:
    /**
     * @struct CtServicePack
     * @brief Represents a pack containing a task, an ID, and an interval for execution.
     */
    typedef struct _CtServicePack {
        CtTask task;
        std::string id;
        CtUInt32 nslots;
    } CtServicePack;

public:
    /**
     * @brief Constructor for CtServicePool.
     * @param nworkers The number of worker threads in the service pool.
     * @param slot_time The time interval for each "slot" in milliseconds. Default is 10 milliseconds.
     */
    EXPORTED_API CtServicePool(CtUInt32 nworkers);

    /**
     * @brief Destructor for CtServicePool.
     */
    EXPORTED_API ~CtServicePool();

    /**
     * @brief Add a task to the service pool with a specified interval and an optional ID.
     * @param nslots The interval in slots for executing the task.
     * @param id An optional ID for the task.
     * @param task The task to be added.
     */
    EXPORTED_API void addTask(CtUInt32 nslots, std::string id, CtTask& task);

    /**
     * @brief Add a task to the service pool with a specified interval and an optional ID.
     * @param nslots The interval in slots for executing the task.
     * @param id An optional ID for the task.
     * @param func The task function to be added.
     * @param fargs The task function's arguments to be added.
     */
    template <typename F, typename... FArgs>
    EXPORTED_API void addTaskFunc(CtUInt32 nslots, std::string id, F&& func, FArgs&&... fargs);

    /**
     * @brief Remove a task from the service pool based on its ID.
     * @param id The ID of the task to be removed.
     */
    EXPORTED_API void removeTask(std::string id);

    /**
     * @brief Start the services provided by the service pool.
     */
    EXPORTED_API void startServices();

    /**
     * @brief Shutdown the services provided by the service pool.
     */
    EXPORTED_API void shutdownServices();

    /**
     * @brief Get slot time.
     */
    EXPORTED_API CtUInt32 getSlotTime();

    /**
     * @brief Set slot time.
     */
    EXPORTED_API void setSlotTime(CtUInt32 nslots);

private:
    /**
     * @brief Overridden loop function from CtThread, representing the main thread logic.
     */
    void loop() override;

private:
    CtUInt32 m_nworkers; ///< The number of worker threads in the service pool.
    CtUInt32 m_slot_cnt; ///< Counter for the current slot.
    std::vector<CtServicePack> m_tasks; ///< Vector of tasks in the service pool.
    std::mutex m_mtx_control; ///< Mutex for controlling access to shared resources.
    CtWorkerPool m_worker_pool; ///< Worker pool for executing tasks.
    CtTimer m_timer; ///< Timer for tracking time intervals.
    uint64_t m_exec_time; ///< Variable used for time tracking during a loop.
};

template <typename F, typename... FArgs>
void CtServicePool::addTaskFunc(CtUInt32 nslots, std::string id, F&& func, FArgs&&... fargs) {
    CtTask s_task;
    s_task.setTaskFunc(std::bind(func, std::forward<FArgs>(fargs)...));
    addTask(nslots, id, s_task);
};

#endif //INCLUDE_CTSERVICEPOOL_HPP_
