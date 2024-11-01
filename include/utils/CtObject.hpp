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
 * @file CtObject.hpp
 * @brief 
 * @date 02-02-2024
 * 
 */

#ifndef INCLUDE_CTOBJECT_HPP_
#define INCLUDE_CTOBJECT_HPP_

#include "definitions.hpp"
#include "CtTypes.hpp"

#include "utils/CtTask.hpp"
#include "threading/CtWorkerPool.hpp"

#include <string>
#include <map>
#include <mutex>
#include <functional>

/**
 * @brief This abstract class can be used as a base class for objects that can trigger events.
 * 
 */
class CtObject {
public:
    /**
     * @brief This method connects an event code with a function that should be triggered.
     * 
     * @param p_obj The object that hosts the event.
     * @param p_eventCode The event code.
     * @param func The function to be executed.
     * @param fargs The parameters of the function that will be executed.
     */
    template <typename F, typename... FArgs>
    EXPORTED_API static void connectEvent(CtObject* p_obj, CtUInt32 p_eventCode, F&& func, FArgs&&... fargs);

    /**
     * @brief This method connects an event code with a function that should be triggered.
     * 
     * @param p_obj The object that hosts the event.
     * @param p_eventCode The event code.
     * @param p_task The task to be executed.
     */
    EXPORTED_API static void connectEvent(CtObject* p_obj, CtUInt32 p_eventCode, CtTask& p_task);

    /**
     * @brief This method connects an event code with a function that should be triggered.
     * 
     * @param p_eventCode The event code.
     * @param func The function to be executed.
     * @param fargs The parameters of the function that will be executed.
     */
    template <typename F, typename... FArgs>
    EXPORTED_API void connectEvent(CtUInt32 p_eventCode, F&& func, FArgs&&... fargs);

    /**
     * @brief This method connects an event code with a function that should be triggered.
     * 
     * @param p_eventCode The event code.
     * @param p_task The task to be executed.
     */
    EXPORTED_API void connectEvent(CtUInt32 p_eventCode, CtTask& p_task);

    /**
     * @brief This method is equivalent to join() function of CtThread.
     * 
     */
    EXPORTED_API void waitPendingEvents();

protected:
    /**
     * @brief The constructor of the CtObject class.
     * 
     */
    EXPORTED_API CtObject();

    /**
     * @brief The destructor of the CtObject class.
     * 
     */
    EXPORTED_API ~CtObject();

    /**
     * @brief This method triggers a specific event code.
     * 
     * @param p_eventCode The event code to be triggered.
     */
    EXPORTED_API void triggerEvent(CtUInt32 p_eventCode);

    /**
     * @brief This event registers a specific event code.
     * 
     * @param p_eventCode The event code to be registered.
     */
    EXPORTED_API void registerEvent(CtUInt32 p_eventCode);

private:
    /**
     * @brief This methods checks if a specific event code is already registered in this object.
     * 
     * @param p_eventCode The event code to be checked.
     */
    EXPORTED_API bool hasEvent(CtUInt32 p_eventCode);

private:
    std::mutex m_mtx_control; ///< Mutex for controlling access to shared resources.
    std::vector<uint8_t> m_events; ///< This vector contains all the registered event codes.
    std::multimap<uint8_t, CtTask> m_triggers; ///< This map represents a list of tasks that should be triggered for each event code.
    CtWorkerPool m_pool; ///< This CtWorkerPool executes the triggered tasks.
};

template <typename F, typename... FArgs>
void CtObject::connectEvent(CtObject* p_obj, CtUInt32 p_eventCode, F&& func, FArgs&&... fargs) {
    CtTask s_task;
    s_task.setTaskFunc(std::bind(func, std::forward<FArgs>(fargs)...));
    p_obj->connectEvent(p_eventCode, s_task);
};

template <typename F, typename... FArgs>
void CtObject::connectEvent(CtUInt32 p_eventCode, F&& func, FArgs&&... fargs) {
    CtTask s_task;
    s_task.setTaskFunc(std::bind(func, std::forward<FArgs>(fargs)...));
    connectEvent(p_eventCode, s_task);
};

#endif //INCLUDE_CTOBJECT_HPP_