#include <iostream>
#include<vector>
#include<string>
#include<limits>

//3.考虑函数声明：函数的返回值，函数的传参，函数的作用

void printMenu();
void addTask(std::vector<std::string>& tasks);
void viewTasks(const std::vector<std::string>& tasks);
void deleteTask(std::vector<std::string>& tasks);

int main()
{
	//1.优先考虑数据容器类型，数据结构
	std::vector<std::string> tasks;
	int choice = 0;
	std::cout << "===欢迎使用简单的待办事项应用程序！===" << std::endl;

	//2.操作逻辑
	do {
		printMenu();
		std::cin >> choice;

		//清除输入缓冲区，防止后续getline读取错误
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice) {
		case 1:
			addTask(tasks);
			break;
		case 2:
			viewTasks(tasks);
			break;
		case 3:
			deleteTask(tasks);
			break;
		case 4:
			std::cout << "感谢使用，再见！" << std::endl;
			break;
		default:
			std::cout << "无效的选择，请重新输入。" << std::endl;

		}
	} 
	while (choice != 4);
		return 0;
	
}

//打印主菜单
void printMenu() {
	std::cout << "\n---主菜单---" << std::endl;
	std::cout << "1. 添加任务" << std::endl;
	std::cout << "2. 查看任务" << std::endl;
	std::cout << "3. 删除任务" << std::endl;
	std::cout << "4. 退出" << std::endl;
	std::cout << "请选择操作（1-4）：";
}

//添加任务
void addTask(std::vector<std::string>& tasks) {
	std::string task;
	std::cout << "请输入要添加的任务：";
	std::getline(std::cin, task);
	
	if (!task.empty()) {
		tasks.push_back(task);
		std::cout << "任务已添加！" << std::endl;
	} else {
		std::cout << "任务不能为空，请重新输入。" << std::endl;
	}
}

//查看任务
void viewTasks(const std::vector<std::string>& tasks) {
	if (tasks.empty()) {
		std::cout << "没有待办事项。" << std::endl;
		return;
	}
	std::cout << "\n---待办事项列表---" << std::endl;
	for (size_t i = 0; i < tasks.size(); ++i) {
		std::cout << i + 1 << ". " << tasks[i] << std::endl;
	}
	std::cout << "总共有 " << tasks.size() << " 个待办事项。" << std::endl;
}

//删除任务
void deleteTask(std::vector<std::string>& tasks) {
	if (tasks.empty()) {
		std::cout << "没有待办事项可删除。" << std::endl;
		return;
	}

	viewTasks(tasks);//先显示所有任务，方便用户选择要删除的任务编号
	int taskNumber;
	std::cout << "请输入要删除的任务编号：";
	std::cin >> taskNumber;

	//检查输入的任务编号是否有效
	if (std::cin.fail()) {
		std::cin.clear(); //清除错误状态
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //清除输入缓冲区
		std::cout << "无效的输入，请输入有效数字。" << std::endl;
		return;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //清除输入缓冲区
	if (taskNumber >= 1 && taskNumber <= static_cast<int>(tasks.size())) {
		std::string removedTask = tasks[taskNumber - 1];
		tasks.erase(tasks.begin() + taskNumber - 1);
		std::cout << "任务 \"" << removedTask << "\" 已删除！" << std::endl;
	}
	else {
				std::cout << "无效的任务编号，请重新输入。" << std::endl;
	}
		
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
