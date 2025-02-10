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
 * @file CtService.hpp
 * @brief CtService class header file.
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTSERVICE_HPP_
#define INCLUDE_CTSERVICE_HPP_

#include "core.hpp"

#include "threading/CtThread.hpp"
#include "threading/CtWorker.hpp"
#include "threading/CtTask.hpp"
#include "time/CtTimer.hpp"

/**
 * @class CtService
 * @brief A class representing a service that runs a given task at regular intervals using a worker thread.
 * 
 * @ref FR-005-005-001
 * @ref FR-005-005-008
 * @ref FR-005-005-013
 * 
 * @details
 * The CtService class provides a mechanism for running a task at regular intervals using a worker thread.
 * The service can be configured to run the task immediately or after a certain number of time slots.
 * The service can be stopped and started at any time. The service is thread-safe and can be used in multi-threaded environments.
 * 
 * 
 * @code {.cpp}
 * // create a service that runs a task every 1000 milliseconds
 * CtService service(1000, [](){ std::cout << "Hello from service!" << std::endl; });
 * service.runService();
 * // do something else
 * service.stopService();
 * @endcode
 */
class CtService : private CtThread {
public:
    /**
     * @brief Constructor for CtService.
     * 
     * @ref FR-005-005-002
     * 
     * @param nslots The number of time slots between task executions. Default is 0 (run immediately).
     * @param task The task to be executed by the service.
     */
    EXPORTED_API CtService(CtUInt64 nslots, const CtTask& task);

    /**
     * @brief Constructor for CtService.
     * 
     * @ref FR-005-005-002
     * 
     * @param nslots The number of time slots between task executions. Default is 0 (run immediately).
     * @param func The task function to be executed by the service.
     * @param fargs The task function's parameters.
     */
    template <typename F, typename... FArgs>
    EXPORTED_API CtService(CtUInt64 nslots, const F&& func, FArgs&&... fargs);

    /**
     * @brief Destructor for CtService.
     * 
     * @ref FR-005-005-003
     * @ref FR-005-005-004
     * 
     */
    EXPORTED_API ~CtService();

    /**
     * @brief Run the task provided by the service.
     * 
     * @ref FR-005-005-005
     * @ref FR-005-005-007
     * 
     * @details
     * CtServiceError is thrown in case of service is already running.
     * 
     */
    EXPORTED_API void runService();

    /**
     * @brief Stop the task provided by the service.
     * 
     * @ref FR-005-005-006
     * 
     */
    EXPORTED_API void stopService();

    /**
     * @brief Get the Interval Validity Factor.
     * 
     * @ref FR-005-005-011
     * 
     * @details
     * This method returns a factor that represents the validity of the interval.
     * If the factor is 1, the task is executed at the correct interval. If the factor is less than 1, 
     * the task is executed less frequently than expected. The closer the factor is to 1, the more
     * frequently the task is executed. 
     * 
     * @return float The interval validity factor.
     */
    EXPORTED_API float getIntervalValidity();

public:
    /**
     * @brief The time interval for each "slot" in milliseconds.
     * 
     * @ref FR-005-005-012
     * 
     */
    static CtUInt32 m_slot_time;

private:
    /**
     * @brief Overridden run function from CtThread, representing the main logic of the service.
     * 
     * @ref FR-005-005-008
     * @ref FR-005-005-009
     * @ref FR-005-005-010
     * 
     */
    void loop() override;

private:
    CtWorker m_worker;              /*!< Worker for executing the task. */
    CtUInt64 m_nslots;              /*!< The number of slots to wait before rerunning the service. */
    CtUInt32 m_skip_ctr;            /*!< Task execution skip counter. */
    CtUInt32 m_exec_ctr;            /*!< Total loop counter. */
};

template <typename F, typename... FArgs>
CtService::CtService(CtUInt64 nslots, const F&& func, FArgs&&... fargs) : m_nslots(nslots){
    CtTask s_task;
    s_task.setTaskFunc(std::bind(func, std::forward<FArgs>(fargs)...));
    m_worker.setTask(s_task);
};

#endif //INCLUDE_CTSERVICE_HPP_
