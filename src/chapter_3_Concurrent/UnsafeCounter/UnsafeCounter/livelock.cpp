#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> resource_available{ false };

void worker(int id) {
    int attempts = 0;
    while (attempts < 5) {
        // 尝试获取资源
        bool expected = false;
        if (resource_available.compare_exchange_weak(expected, true)) {
            std::cout << "Worker " << id << " got the resource" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            resource_available = false;
            return;
        }

        // 活锁：不断重试但可能永远无法获得资源
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        attempts++;
    }
    std::cout << "Worker " << id << " gave up" << std::endl;
}