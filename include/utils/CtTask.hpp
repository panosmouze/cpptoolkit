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

#include "definitions.hpp"
#include "CtTypes.hpp"

#include <functional>

/**
 * @brief Represents a task class that encapsulates a callable function (task) and a callback function.
 *    The task function is the main function that will be executed. The callback function is the function 
 *    that will be executed after the task function. The task and callback functions can have arguments.
 *    This method can be used to organise a specific functionality and post process of it in a single object.
 *    
 */
class CtTask {
public:
    /**
     * @brief Default constructor for CtTask.
     * Initializes task and callback with empty lambda functions.
     * 
     */
    EXPORTED_API CtTask();

    /**
     * @brief Copy constructor for CtTask.
     * Copies the task and callback from another CtTask object.
     * 
     * @param other The CtTask object to copy.
     * 
     */
    EXPORTED_API CtTask(const CtTask& other);

    /**
     * @brief Destructor for CtTask.
     */
    EXPORTED_API ~CtTask();

    /**
     * @brief Set the main task function. The task function can also have arguments.
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
    EXPORTED_API void setTaskFunc(F&& func, FArgs&&... fargs);

    /**
     * @brief Set the callback function. The callback function can also have arguments.
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
    EXPORTED_API void setCallbackFunc(C&& callback, CArgs&&... cargs);

    /**
     * @brief Get the main task function.
     * 
     * @return The main task function.
     */
    EXPORTED_API std::function<void()> getTaskFunc();

    /**
     * @brief Get the callback function.
     * 
     * @return The callback function.
     */
    EXPORTED_API std::function<void()> getCallbackFunc();

    /**
     * @brief Assignment operator for CtTask.
     * Copies the task and callback from another CtTask object.
     * 
     * @param other The CtTask object to copy.
     * 
     * @return CtTask& Reference to the current CtTask object.
     */
    EXPORTED_API CtTask& operator=(const CtTask& other);

private:
    std::function<void()> m_task;           // The main task function
    std::function<void()> m_callback;       // The callback function
};

template <typename F, typename... FArgs>
void CtTask::setTaskFunc(F&& func, FArgs&&... fargs) {
    m_task = std::bind(func, std::forward<FArgs>(fargs)...);
};

template <typename C, typename... CArgs>
void CtTask::setCallbackFunc(C&& callback, CArgs&&... cargs) {
    m_callback = std::bind(callback, std::forward<CArgs>(cargs)...);
};

#endif //INCLUDE_CTTASK_HPP_
