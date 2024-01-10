/*
 * CtLog.cpp
 *
 *  Created on: Jan 10, 2023
 *      Author: Mouzenidis Panagiotis
 */
#include "io/sinks/CtLog.hpp"

#include <iostream>

CtLog::CtLog() : CtSink() {

}

CtLog::~CtLog() {

}

void CtLog::write(std::string logEntry) {
    lock();
    std::cout << logEntry << std::endl;
    unlock();
}