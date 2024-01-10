/*
 * CtLogSink.cpp
 *
 *  Created on: Jan 10, 2023
 *      Author: Mouzenidis Panagiotis
 */
#include "io/sinks/CtLogSink.hpp"

#include <iostream>

CtLogSink::CtLogSink() : CtSink() {

}

CtLogSink::~CtLogSink() {

}

void CtLogSink::write(std::string logEntry) {
    lock();
    std::cout << logEntry << std::endl;
    unlock();
}