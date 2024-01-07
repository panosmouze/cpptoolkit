/*
 * CtTask.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#ifndef INCLUDE_UTILS_CTTASK_HPP_
#define INCLUDE_UTILS_CTTASK_HPP_

#include "definitions.hpp"
#include <functional>

/**
 * @class CtTask
 * @brief Represents a task class that encapsulates a callable function (task) and a callback function.
 */
class CtTask {
public:
    /**
     * @brief Default constructor for CtTask.
     * Initializes task and callback with empty lambda functions.
     */
    EXPORTED_API CtTask();

    /**
     * @brief Copy constructor for CtTask.
     * Copies the task and callback from another CtTask object.
     * @param other The CtTask object to copy.
     */
    EXPORTED_API CtTask(const CtTask& other);

    /**
     * @brief Destructor for CtTask.
     */
    EXPORTED_API ~CtTask();

    /**
     * @brief Set the main task function.
     * @tparam F Type of the callable function.
     * @tparam FArgs Types of the arguments for the callable function.
     * @param func The callable function.
     * @param fargs The arguments for the callable function.
     */
    template <typename F, typename... FArgs>
    EXPORTED_API void setTaskFunc(F&& func, FArgs&&... fargs);

    /**
     * @brief Set the callback function.
     * @tparam C Type of the callable function.
     * @tparam CArgs Types of the arguments for the callable function.
     * @param callback The callable function.
     * @param cargs The arguments for the callable function.
     */
    template <typename C, typename... CArgs>
    EXPORTED_API void setCallbackFunc(C&& callback, CArgs&&... cargs);

    /**
     * @brief Get the main task function.
     * @return The main task function.
     */
    EXPORTED_API std::function<void()> getTaskFunc();

    /**
     * @brief Get the callback function.
     * @return The callback function.
     */
    EXPORTED_API std::function<void()> getCallbackFunc();

    /**
     * @brief Assignment operator for CtTask.
     * Copies the task and callback from another CtTask object.
     * @param other The CtTask object to copy.
     * @return Reference to the current CtTask object.
     */
    EXPORTED_API CtTask& operator=(const CtTask& other);

private:
    std::function<void()> m_task; /**< The main task function. */
    std::function<void()> m_callback; /**< The callback function. */
};

template <typename F, typename... FArgs>
EXPORTED_API void CtTask::setTaskFunc(F&& func, FArgs&&... fargs) {
    m_task = std::bind(std::forward<F>(func), std::get<FArgs>(fargs)...);
};

template <typename C, typename... CArgs>
EXPORTED_API void CtTask::setCallbackFunc(C&& callback, CArgs&&... cargs) {
    m_callback = std::bind(std::forward<C>(callback), std::get<CArgs>(cargs)...);
};

#endif /* INCLUDE_UTILS_CTTASK_HPP_ */
