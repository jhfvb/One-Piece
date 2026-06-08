#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <vector>
#include <sstream>

std::mutex io_mutex;
std::atomic<bool> running{ true };

// CPU密集型任务（饥饿制造者）
void cpu_intensive_worker(int id) {
    std::stringstream ss;
    ss << "CPU intensive worker " << id << " started\n";
    std::lock_guard<std::mutex> io_lock(io_mutex);
    std::cout << ss.str();

    long long counter = 0;
    while (running) {
        // 纯CPU计算，不释放CPU
        for (int i = 0; i < 1000000; ++i) {
            counter += i * i;
        }

        // 偶尔输出进度
        if (counter % 1000000000LL < 1000000LL) {
            std::stringstream ss2;
            ss2 << "CPU worker " << id << " progress: " << counter << "\n";
            std::lock_guard<std::mutex> io_lock2(io_mutex);
            std::cout << ss2.str();
        }
    }
}

// IO密集型任务（被饥饿的线程）
void io_intensive_worker(int id) {
    std::stringstream ss;
    ss << "IO worker " << id << " started\n";
    std::lock_guard<std::mutex> io_lock(io_mutex);
    std::cout << ss.str();

    int iterations = 0;
    while (running && iterations < 50) {
        // 等待IO（sleep模拟）
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::stringstream ss2;
        ss2 << "IO worker " << id << " completed iteration "
            << ++iterations << "\n";
        std::lock_guard<std::mutex> io_lock2(io_mutex);
        std::cout << ss2.str();
    }
}

void demonstrate_cpu_starvation() {
    std::cout << "Starting CPU starvation demo...\n";
    std::cout << "Notice: CPU workers may starve IO workers!\n\n";

    std::vector<std::thread> threads;

    // 启动2个CPU密集型线程
    for (int i = 1; i <= 2; ++i) {
        threads.emplace_back(cpu_intensive_worker, i);
    }

    // 启动3个IO密集型线程（可能被饥饿）
    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back(io_intensive_worker, i);
    }

    // 运行一段时间
    std::this_thread::sleep_for(std::chrono::seconds(5));

    running = false;

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "\nDemo complete. IO workers may have been starved by CPU workers.\n";
}