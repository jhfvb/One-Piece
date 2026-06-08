#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1, mutex2;

void thread_a() {
    std::lock_guard<std::mutex> lock1(mutex1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // 这里会死锁，因为thread_b持有mutex2
    std::lock_guard<std::mutex> lock2(mutex2);
    std::cout << "Thread A completed" << std::endl;
}

void thread_b() {
    std::lock_guard<std::mutex> lock2(mutex2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // 这里会死锁，因为thread_a持有mutex1
    std::lock_guard<std::mutex> lock1(mutex1);
    std::cout << "Thread B completed" << std::endl;
}

void demonstrate_deadlock() {
    std::thread t1(thread_a);
    std::thread t2(thread_b);

    t1.join();
    t2.join();  // 程序可能永远卡在这里
}