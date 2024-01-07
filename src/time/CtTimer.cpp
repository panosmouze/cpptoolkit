/*
 * CtTimer.hpp
 *
 *  Created on: Nov 12, 2023
 *      Author: Mouzenidis Panagiotis
 */

#include "time/CtTimer.hpp"

CtTimer::CtTimer() {
    m_reference = 0;
}

CtTimer::~CtTimer() {
    
}

void CtTimer::tic() {
    m_reference = current();
}

uint64_t CtTimer::toc() {
    return current() - m_reference;
}

uint64_t CtTimer::current() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()
    ).count();
}
