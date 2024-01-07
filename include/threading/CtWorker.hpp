/*
 * CtWorker.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_THREADING_CTWORKER_HPP_
#define INCLUDE_THREADING_CTWORKER_HPP_

#include "definitions.hpp"
#include "utils/CtTask.hpp"

#include <thread>
#include <atomic>
#include <functional>

/**
 * @class CtWorker
 * @brief Represents a worker thread that can execute tasks asynchronously.
 */
class CtWorker {
public:
    /**
     * @brief Constructor for CtWorker.
     */
    EXPORTED_API CtWorker();

    /**
     * @brief Destructor for CtWorker.
     */
    EXPORTED_API ~CtWorker();

    /**
     * @brief Returns true if the worker is currently running.
     * 
     * @return EXPORTED_API Worker status.
     */
    EXPORTED_API bool isRunning();

    /**
     * @brief Run the task assigned to the worker.
     */
    EXPORTED_API void runTask();

    /**
     * @brief Join the worker's thread, waiting for the task to complete.
     */
    EXPORTED_API void joinTask();

    /**
     * @brief Set a task for the worker to execute.
     * @param task The task to be executed by the worker.
     * @param callback The callback function to be executed after the task is completed.
     *                 Default is an empty lambda function.
     */
    EXPORTED_API void setTask(CtTask& task, std::function<void()> callback = []{});

    /**
     * @brief Set a task function for the worker to execute.
     * 
     * @param func The task function to be executed by the worker.
     * @param fargs The arguments of the executed task function.
     */
    template <typename F, typename... FArgs>
    EXPORTED_API void setTaskFunc(F&& func, FArgs&&... fargs);

private:
    /**
     * @brief Helper function that checks if the CtWorker is already running and returns an exception.
     */
    void alreadyRunningCheck();

    /**
     * @brief Helper function set the m_running flag.
     */
    void setRunning(bool running);

private:
    CtTask m_task; ///< The task assigned to the worker.
    std::atomic<bool> m_running;
    std::thread m_thread; ///< The worker's thread.
    std::function<void()> m_callback; ///< Callback function to be executed after the task is completed.
};

template <typename F, typename... FArgs>
EXPORTED_API void CtWorker::setTaskFunc(F&& func, FArgs&&... fargs) {
    CtTask s_task;
    s_task.setTaskFunc(std::bind(std::forward<F>(func), std::get<FArgs>(fargs)...));
    setTask(s_task);
};

#endif /* INCLUDE_THREADING_CTWORKER_HPP_ */
