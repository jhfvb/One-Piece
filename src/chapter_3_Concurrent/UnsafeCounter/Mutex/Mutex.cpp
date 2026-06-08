// Mutex.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

class safeCounter {
private:
    std::mutex _mutex;
    int _count = 0;

public:
    void increment() {
       // _mutex.lock();
        {
            std::lock_guard<std::mutex> lock(_mutex); // 使用lock_guard自动管理锁的生命周期
            // 这里存在数据竞争！
            _count = _count + 1;
		}//加大括号，确保lock_guard在这里被销毁，释放锁
       // _mutex.unlock();
    }

    int get_count() const { return _count; }
};

void demonstrate_data_race() {
    safeCounter counter;
    std::vector<std::thread> threads;

    // 创建10个线程，每个增加计数器1000次
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&counter]() {
            for (int j = 0; j < 1000; ++j) {
                counter.increment();
            }
            });
    }

    for (auto& t : threads) {
        t.join();
    }

    // 结果将永远是10000！
    std::cout << "Final count: " << counter.get_count() << std::endl;
}
int main()
{
    demonstrate_data_race();
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
