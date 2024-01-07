#include "CtThreading.hpp"
#include "CtUtils.hpp"

#include <iostream>
#include <chrono>
#include <thread>

int main() {
    CtServicePool pool(10);
    int cnt[150] = {0};
    for (int i = 0; i < 150; i++) {
        pool.addTaskFunc(100, std::to_string(i), [&cnt, i](){
            cnt[i]++;
        });
    }
    
    CtThread::sleepFor(2001);
    pool.shutdownServices();
    for (int i = 0; i < 150; i++) {
        std::cout << i << ": " << cnt[i] << std::endl;
    }
    return 0;
}
