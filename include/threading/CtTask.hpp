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
 * @file CtTask.hpp
 * @brief CtTask class header file.
 * @date 18-01-2024
 * 
 */

#ifndef INCLUDE_CTTASK_HPP_
#define INCLUDE_CTTASK_HPP_

#include "core.hpp"

#include <functional>

/**
 * @brief Represents a task class that encapsulates a callable function (task) and a callback function.
 * @details 
 * The task function is the main function that will be executed. The callback function is the function
 * that will be executed after the task function. The task and callback functions can have arguments.
 * This method can be used to organise a specific functionality and post process of it in a single object.
 *
 * @code{.cpp}
 * CtTask task;
 * // Set the task function to a lambda function that prints the sum of two integers.
 * task.setTaskFunc([](int a, int b) {
 *   std::cout << "Task function: " << a + b << std::endl;
 * }, 1, 2);
 * task.setCallbackFunc([](int a, int b) {
 *   std::cout << "Callback function: " << a - b << std::endl;
 * }, 1, 2);
 * 
 * // Set the task function to a function with arguments.
 * task.setTaskFunc(func, arg1, arg2);
 * task.setCallbackFunc(callbackFunc, arg1, arg2);
 * @endcode
 */
class CtTask {
public:
    /**
     * @brief Default constructor for CtTask.
     * Initializes task and callback with empty lambda functions.
     * 
     * @ref FR-005-001-002
     * 
     */
    EXPORTED_API explicit CtTask();

    /**
     * @brief Copy constructor for CtTask.
     * Copies the task and callback from another CtTask object.
     * 
     * @ref FR-005-001-001
     * @ref FR-005-001-002
     * 
     * @param other The CtTask object to copy.
     * 
     */
    EXPORTED_API CtTask(const CtTask& other);

    /**
     * @brief Destructor for CtTask.
     * 
     * @ref FR-005-001-003
     */
    EXPORTED_API ~CtTask();

    /**
     * @brief Set the main task function. The task function can also have arguments.
     * 
     * @ref FR-005-001-001
     * @ref FR-005-001-006
     * 
     * @tparam F Type of the callable function.
     * @tparam FArgs Types of the arguments for the callable function.
     * 
     * @param func The callable function.
     * @param fargs The arguments for the callable function.
     * 
     * @return void
     */
    template <typename F, typename... FArgs>
    EXPORTED_API void setTaskFunc(const F&& func, FArgs&&... fargs);

    /**
     * @brief Set the callback function. The callback function can also have arguments.
     * 
     * @ref FR-005-001-001
     * @ref FR-005-001-007
     * 
     * @tparam C Type of the callable function.
     * @tparam CArgs Types of the arguments for the callable function.
     * 
     * @param callback The callable function.
     * @param cargs The arguments for the callable function.
     * 
     * @return void
     */
    template <typename C, typename... CArgs>
    EXPORTED_API void setCallbackFunc(const C&& callback, CArgs&&... cargs);

    /**
     * @brief Get the main task function.
     * 
     * @ref FR-005-001-001
     * @ref FR-005-001-004
     * 
     * @return The main task function.
     */
    EXPORTED_API std::function<void()> getTaskFunc();

    /**
     * @brief Get the callback function.
     * 
     * @ref FR-005-001-001
     * @ref FR-005-001-005
     * 
     * @return The callback function.
     */
    EXPORTED_API std::function<void()> getCallbackFunc();

    /**
     * @brief Assignment operator for CtTask.
     * Copies the task and callback from another CtTask object.
     * 
     * @ref FR-005-001-001
     * @ref FR-005-001-008
     * 
     * @param other The CtTask object to copy.
     * 
     * @return CtTask& Reference to the current CtTask object.
     */
    EXPORTED_API CtTask& operator=(const CtTask& other);

private:
    std::function<void()> m_task;           /*!< The main task function */
    std::function<void()> m_callback;       /*!< The callback function */
};

template <typename F, typename... FArgs>
void CtTask::setTaskFunc(const F&& func, FArgs&&... fargs) {
    m_task = std::bind(func, std::forward<FArgs>(fargs)...);
};

template <typename C, typename... CArgs>
void CtTask::setCallbackFunc(const C&& callback, CArgs&&... cargs) {
    m_callback = std::bind(callback, std::forward<CArgs>(cargs)...);
};

#endif //INCLUDE_CTTASK_HPP_
