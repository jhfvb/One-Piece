#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

class BasicConditionVariable {
private:
    std::mutex mutex_;
    std::condition_variable cv_;
	bool data_ready_ = false;//标志位，数据是否准备好
    int shared_data_ = 0;

	//队列是否为空
	//生产者是往队列里放数据，消费者是从队列里取数据，所以生产者需要判断队列是否满了，消费者需要判断队列是否空了
public:
	//生产者线程函数
    void producer() {
        std::cout << "Producer: starting work..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        {
            std::lock_guard<std::mutex> lock(mutex_);
            shared_data_ = 42;
            data_ready_ = true;
            std::cout << "Producer: data prepared, notifying..." << std::endl;
        }

        cv_.notify_one();  // 通知一个等待的线程
    }
	//消费者线程函数
    void consumer() {
        std::cout << "Consumer: waiting for data..." << std::endl;

        std::unique_lock<std::mutex> lock(mutex_);

        // 等待条件满足
        cv_.wait(lock, [this]() {
            std::cout << "Consumer: checking condition..." << std::endl;
            return data_ready_;
            });

        // 条件满足，处理数据
        std::cout << "Consumer: received data = " << shared_data_ << std::endl;
    }
};

int main()
{
	//先生产后消费
    BasicConditionVariable demo;

    std::thread consumer_thread(&BasicConditionVariable::consumer, &demo);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread producer_thread(&BasicConditionVariable::producer, &demo);

    producer_thread.join();
    consumer_thread.join();
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
