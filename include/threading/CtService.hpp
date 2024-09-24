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
 * @brief 
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTSERVICE_HPP_
#define INCLUDE_CTSERVICE_HPP_

#include "definitions.hpp"
#include "CtTypes.hpp"
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
    EXPORTED_API CtService(CtUInt32 nslots, F&& func, FArgs&&... fargs);

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
    static CtUInt32 m_slot_time; ///< The time interval for each "slot" in milliseconds.

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
CtService::CtService(CtUInt32 nslots, F&& func, FArgs&&... fargs) : m_nslots(nslots){
    CtTask s_task;
    s_task.setTaskFunc(std::bind(func, std::forward<FArgs>(fargs)...));
    m_worker.setTask(s_task);
};

#endif //INCLUDE_CTSERVICE_HPP_
