#include "CtThreading.hpp"
#include "CtUtils.hpp"

#include <iostream>
#include <chrono>
#include <thread>

int main() {
    CtWorker worker;
    worker.setTaskFunc([](){
        std::cout << "Task start" << std::endl;
        CtThread::sleepFor(1000);
        std::cout << "Task stop" << std::endl;
    });
    worker.runTask();
    worker.joinTask();
    return 0;
}
