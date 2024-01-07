#include "CtThreading.hpp"
#include "CtUtils.hpp"

#include <iostream>
#include <chrono>
#include <thread>

int main() {
    int cnt = 0;
    CtService service(100, [&cnt](){cnt++;});
    service.runService();
    
    CtThread::sleepFor(1900);
    service.stopService();
    std::cout << cnt << std::endl;
    return 0;
}
