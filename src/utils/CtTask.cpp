/*
 * CtTask.cpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#include "utils/CtTask.hpp"

CtTask::CtTask() {
    m_task = []{};
    m_callback = []{};
}

CtTask::CtTask(const CtTask& other) {
    m_task = other.m_task;
    m_callback = other.m_callback;
}

CtTask::~CtTask() {

}

std::function<void()> CtTask::getTaskFunc() {
    return m_task;
}

std::function<void()> CtTask::getCallbackFunc() {
    return m_callback;
}

CtTask& CtTask::operator=(const CtTask& other) {
    if (this != &other) {
        m_task = other.m_task;
        m_callback = other.m_callback;
    }
    return *this;
}
