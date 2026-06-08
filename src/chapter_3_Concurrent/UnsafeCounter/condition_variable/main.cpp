#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;//一个条件变量，很简单的实现
bool ready = false;//标志位，数据是否准备好

// 1. 基本的wait - 可能产生虚假唤醒
void basic_wait() {
    std::unique_lock<std::mutex> lock(mtx);

    // 不推荐：可能因为虚假唤醒而提前返回
    cv.wait(lock);
    std::cout << "Basic wait: awakened" << std::endl;
}

// 2. 带谓词的wait - 推荐使用
void predicate_wait() {
    std::unique_lock<std::mutex> lock(mtx);

    // 推荐：使用谓词，带检查条件
    cv.wait(lock, []() {
        return ready;
        });
    //相当于一个while循环
    std::cout << "Predicate wait: condition met" << std::endl;
}

// 3. 带超时的wait_for
void timed_wait_for() {
    std::unique_lock<std::mutex> lock(mtx);

    auto status = cv.wait_for(lock, std::chrono::seconds(2), []() {
        return ready;
        });

    if (status) {
        std::cout << "Timed wait: condition met within timeout" << std::endl;
    }
    else {
        std::cout << "Timed wait: timeout reached" << std::endl;
    }
}

// 4. 带绝对时间的wait_until
void timed_wait_until() {
    std::unique_lock<std::mutex> lock(mtx);

    auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(3);

    auto status = cv.wait_until(lock, deadline, []() {
        return ready;
        });

    if (status) {
        std::cout << "Wait until: condition met before deadline" << std::endl;
    }
    else {
        std::cout << "Wait until: deadline reached" << std::endl;
    }
}

void waiting_thread() {
    std::unique_lock<std::mutex> lock(mtx);  // 1. 获取锁

    // cv.wait() 的内部操作：
    //函数，等待为true 卡在这里等待
    cv.wait(lock, [] { return ready; });
    // 等效于：
    // while (!ready) {
    //     lock.unlock();       // 2. 暂时释放锁，// ⚠️ lock_guard 没有这个方法
    //     // 进入等待队列（操作系统级）
    //	   internal_wait();
    //     lock.lock();         // 3. 被唤醒后重新获取锁// ⚠️ lock_guard 没有这个方法
    // }
    //需要执行的操作
    std::cout << "waiting_thread! Thread ID: "
        << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void trigger_thread() {
    
    std::unique_lock<std::mutex> lock(mtx);  // 1. 获取锁
    //执行了某些操作
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ready = true;//数据修改
    //调用notify或者notify All 提醒系统
    cv.notify_all();
    std::cout << "trigger_thread! Thread ID: "
        << std::this_thread::get_id() << std::endl;
}

int main()
{
	std::thread waitingthread(waiting_thread);//创建等待线程
    std::thread triggerthread(trigger_thread);//触发线程

    waitingthread.join();
    triggerthread.join();
    std::cout << "Hello World!\n";
}