/*
 * CtServicePool.hpp
 *
 *  Created on: Nov 13, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_THREADING_CTSERVICEPOOL_HPP_
#define INCLUDE_THREADING_CTSERVICEPOOL_HPP_

#include "definitions.hpp"
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
        uint32_t nslots;
    } CtServicePack;

public:
    /**
     * @brief Constructor for CtServicePool.
     * @param nworkers The number of worker threads in the service pool.
     * @param slot_time The time interval for each "slot" in milliseconds. Default is 10 milliseconds.
     */
    EXPORTED_API CtServicePool(uint32_t nworkers);

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
    EXPORTED_API void addTask(uint32_t nslots, std::string id, CtTask& task);

    /**
     * @brief Add a task to the service pool with a specified interval and an optional ID.
     * @param nslots The interval in slots for executing the task.
     * @param id An optional ID for the task.
     * @param func The task function to be added.
     * @param fargs The task function's arguments to be added.
     */
    template <typename F, typename... FArgs>
    EXPORTED_API void addTaskFunc(uint32_t nslots, std::string id, F&& func, FArgs&&... fargs);

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
    EXPORTED_API uint32_t getSlotTime();

    /**
     * @brief Set slot time.
     */
    EXPORTED_API void setSlotTime(uint32_t nslots);

private:
    /**
     * @brief Overridden run function from CtThread, representing the main thread logic.
     */
    void run() override;

private:
    uint32_t m_nworkers; ///< The number of worker threads in the service pool.
    uint32_t m_slot_cnt; ///< Counter for the current slot.
    std::vector<CtServicePack> m_tasks; ///< Vector of tasks in the service pool.
    std::mutex m_mtx_control; ///< Mutex for controlling access to shared resources.
    CtWorkerPool m_worker_pool; ///< Worker pool for executing tasks.
    CtTimer m_timer; ///< Timer for tracking time intervals.
};

template <typename F, typename... FArgs>
EXPORTED_API void CtServicePool::addTaskFunc(uint32_t nslots, std::string id, F&& func, FArgs&&... fargs) {
    CtTask s_task;
    s_task.setTaskFunc(std::bind(std::forward<F>(func), std::get<FArgs>(fargs)...));
    addTask(nslots, id, s_task);
};

#endif /* INCLUDE_THREADING_CTSERVICEPOOL_HPP_ */
