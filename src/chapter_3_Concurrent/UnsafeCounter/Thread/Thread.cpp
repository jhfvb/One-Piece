// Thread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<thread>

//简单的线程函数
void hello_thread() {
	std::cout << "Hello from thread! Theread ID: " << std::this_thread::get_id() << std::endl;
}
// 带循环的线程函数
void worker_thread(int iterations) {
	for (int i = 0; i < iterations; ++i) {
		std::cout << "Worker iteration: " << i
			<< " Thread ID: " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

class ThreadManager {
public:
	// 1. 使用普通函数
	static void static_function(int id) {
		std::cout << "Static function, thread " << id << std::endl;
	}

	// 2. 使用成员函数
	//有一个有一个隐形参数this指针，指向调用成员函数的对象
	void member_function(int id) {
		std::cout << "Member function, thread " << id
			<< " this: " << this << std::endl;
	}

};

struct Functor {
	//操作符重载，重载的（）的操作符，使得对象可以像函数一样被调用
	void operator()(int id) const {
		std::cout << "Functor, thread " << id << std::endl;
	}
};

int main()
{
	ThreadManager manager;
	//方式1：静态函数
	std::thread t1{ ThreadManager::static_function, 1 };//创建线程，传入静态函数和参数
	//方式2：成员函数
	std::thread t3{ &ThreadManager::member_function, &manager, 3 };//创建线程，传入成员函数指针、对象地址和参数
	

	//方式3：lambada表达式

	std::thread t4([](int id) {
		std::cout << "Lambda thread, thread ID: " << std::this_thread::get_id() << std::endl;
		}, 4);

	//方式4：函数对象
	auto f = Functor();
	std::thread t5(f, 5);//创建线程，传入函数对象和参数
	//线程是什么时候开始的？构造完毕处于就绪状态，线程在创建时就开始执行了。
	
	std::thread t2{worker_thread, 5};//空构造，不可执行的线程
	bool ret = t2.joinable();
	t2.join();//等待线程完成，主线程会阻塞直到子线程执行完毕，确保资源被正确回收。
	//t2	.detach();//分离线程，主线程不再管理子线程的生命周期，子线程会在后台继续执行，直到完成。

	//异常是指：主线程先退出了没有管理好子线程，导致子线程成为了孤儿线程，无法被回收，造成资源泄漏。
	std::cout << "t2 joinable: " << ret << std::endl;
	t1.join();//等待线程完成，主线程会阻塞直到子线程执行完毕，确保资源被正确回收。
	t3.join();
	t4.join();
	t5.join();
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
