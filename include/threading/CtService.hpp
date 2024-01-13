/*
 * CtService.hpp
 *
 *  Created on: Nov 13, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_THREADING_CTSERVICE_HPP_
#define INCLUDE_THREADING_CTSERVICE_HPP_

#include "definitions.hpp"
#include "threading/CtThread.hpp"
#include "threading/CtWorker.hpp"
#include "utils/CtTask.hpp"
#include "time/CtTimer.hpp"

/**
 * @class CtService
 * @brief A class representing a service that runs a given task at regular intervals using a worker thread.
 */
class CtService : private CtThread {
public:
    /**
     * @brief Constructor for CtService.
     * @param nslots The time slots between task executions in milliseconds. Default is 0 (run immediately).
     * @param task The task to be executed by the service.
     */
    EXPORTED_API CtService(uint64_t nslots, CtTask& task);

    /**
     * @brief Constructor for CtService.
     * @param nslots The time slots between task executions in milliseconds. Default is 0 (run immediately).
     * @param func The task function to be executed by the service.
     * @param fargs The task function's parameters.
     */
    template <typename F, typename... FArgs>
    EXPORTED_API CtService(uint32_t nslots, F&& func, FArgs&&... fargs);

    /**
     * @brief Destructor for CtService.
     */
    EXPORTED_API ~CtService();

    /**
     * @brief Run the task provided by the service.
     */
    EXPORTED_API void runService();

    /**
     * @brief Stop the task provided by the service.
     */
    EXPORTED_API void stopService();

public:
    static uint32_t m_slot_time; ///< The time interval for each "slot" in milliseconds.

private:
    /**
     * @brief Overridden run function from CtThread, representing the main logic of the service.
     */
    void loop() override;

private:
    CtWorker m_worker; ///< Worker for executing the task.
    uint64_t m_nslots; ///< The number of slots to wait before rerunning the service.
};

template <typename F, typename... FArgs>
EXPORTED_API CtService::CtService(uint32_t nslots, F&& func, FArgs&&... fargs) : m_nslots(nslots){
    CtTask s_task;
    s_task.setTaskFunc(std::bind(std::forward<F>(func), std::get<FArgs>(fargs)...));
    m_worker.setTask(s_task);
};

#endif /* INCLUDE_THREADING_CTSERVICE_HPP_ */
