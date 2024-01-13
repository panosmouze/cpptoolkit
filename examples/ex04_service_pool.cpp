#include "CtThreading.hpp"
#include "CtUtils.hpp"

#include <iostream>
#include <chrono>
#include <thread>

int main() {
    CtService::m_slot_time = 100;
    CtServicePool pool(10);
    int cnt[150] = {0};
    for (int i = 0; i < 150; i++) {
        pool.addTaskFunc(10, std::to_string(i), [&cnt, i](){
            cnt[i]++;
        });
    }
    
    CtThread::sleepFor(60000);
    pool.shutdownServices();
    for (int i = 0; i < 150; i++) {
        std::cout << i << ": " << cnt[i] << std::endl;
    }
    return 0;
}
