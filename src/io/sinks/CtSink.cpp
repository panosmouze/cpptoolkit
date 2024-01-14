/*
 * CtSink.cpp
 *
 *  Created on: Jan 10, 2024
 *      Author: Mouzenidis Panagiotis
 */
#include "io/sinks/CtSink.hpp"

CtSink::CtSink() {

}
CtSink::~CtSink() {

}

void CtSink::lock() {
    m_mtx_control.lock();
}

void CtSink::unlock() {
    m_mtx_control.unlock();
}
