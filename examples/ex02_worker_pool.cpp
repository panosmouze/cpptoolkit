#include "CtThreading.hpp"
#include "CtUtils.hpp"
#include "CtTime.hpp"

#include <iostream>
#include <chrono>
#include <thread>

int main() {
    CtWorkerPool pool(10);
    CtTimer timer;
    timer.tic();
    for (int i = 0; i < 100; i++) {
        pool.addTask([](){
            CtThread::sleepFor(100);
        });
    }
    pool.join();
    std::cout << timer.toc() << std::endl;
    return 0;
}
