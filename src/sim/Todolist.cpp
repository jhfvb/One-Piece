#include "Todolist.h"
#include<iostream>
#include<limits>
#include<algorithm>

//默认构造函数
Todolist::Todolist() : filename("todolist.txt") {
	loadFromFile();//自动加载之前的任务
}

//带文件名参数的构造函数
Todolist::Todolist(const std::string& file) : filename(file) {
	loadFromFile();//自动加载指定文件的任务
}

//添加任务
void Todolist::addTask(const std::string& task) {//：const std::string& 是一种既安全又高效（避免拷贝且不修改）的参数传递方式，适合只读场景。

	if (task.empty()) {
		tasks.push_back(task);
		std::cout << "任务不能为空！" << std::endl;
	}
	else {
		std::cout << "任务已添加: " << task << std::endl;
	}
}

//查看任务
void Todolist::viewTasks() const {
	if (tasks.empty()) {
		std::cout << "当前没有待办任务！" << std::endl;
		return;
	}
	std::cout << "\n---当前待办任务列表---\n";
		displayTasksInternal();
		std::cout << "总计：" << tasks.size() << " 个任务" <<std::endl;
	
}

//删除任务
void Todolist::deleteTask(int taskNumber) {
	if (tasks.empty()){
		std::cout << "当前没有待办任务！" << std::endl;
		return;
	}
	if (isValidIndex(taskNumber)) {
		std::string removedTask = tasks[taskNumber - 1];
		tasks.erase(tasks.begin() + taskNumber - 1); 
		std::cout<<"任务 \""<<removedTask<<"\" 已删除!"<<std::endl;
	}
	else {
		std::cout << "无效的任务编号！" << std::endl;
	}
}

//清空所有任务
void Todolist::clearAllTasks() {
	if (tasks.empty()) {
		std::cout << "当前没有待办任务！" << std::endl;
		return;
	}
	tasks.clear();
	std::cout << "所有任务已清空！" << std::endl;
}

//保存到默认文件
bool Todolist::saveToFile() const {
	return saveToFile(filename);
}

//保存到指定文件
bool Todolist::saveToFile(const std::string& customFilename)const{
std::ofstream outputFile(customFilename);

	if (!outputFile.is_open()) {
		std::cout << "错误：无法打开文件进行保存" <<customFilename<<"!" <<std::endl;
		return false;
	}
	for (const auto& task : tasks) {
		outputFile << task << std::endl;
	}
	outputFile.close();
	std::cout << "成功保存" << tasks.size() << "个任务到文件: " << customFilename << "!" << std::endl;
	return true;
}

//从默认文件加载
bool Todolist::loadFromFile() {
	return loadFromFile(filename);
}

//从指定文件加载
bool Todolist::loadFromFile(const std::string& customFilename) {
	std::ifstream inputFile(customFilename);

	if (!inputFile.is_open()) {
		std::cout << "文件" << customFilename << "不存在或者无法打开，将创建新文件。" << std::endl;
		return false;
	}
	std::vector<std::string>loadeTasks;
	std::string line;
	int loadedCount = 0;

	while (std::getline(inputFile, line)) {
		if (!line.empty()) {
			loadeTasks.push_back(line);
			loadedCount++;
		}
	}
	inputFile.close();

	if (loadedCount > 0) {
		tasks = loadeTasks;//替换当前任务列表
		filename = customFilename;//更新当前文件名
		std::cout << "成功从文件加载了"<<loadedCount<<"个任务!"<<std::endl;
		return true;
	}
	return false;
}

//获取任务数量
int Todolist::getTaskCount()const {
	return tasks.size();
}

//检查是否为空
bool Todolist::isEmpty()const {
	return tasks.empty();
}

//获取特定任务
std::string Todolist::getTask(int index) const {
	if (isValidIndex(index)) {
		return tasks[index-1];
	}
	else {
		std::cout << "无效的任务编号！" << std::endl;
		return "";
	}
}

//获取文件名
std::string Todolist::getFilename() const {
	return filename;
}

//设置文件名
void Todolist::setFilename(const std::string& newFilename) {
	filename = newFilename;
	std::cout << "文件名已更新为: " << filename << std::endl;
}

//显示统计信息
void Todolist::displayStatistics() const {
	std::cout << "\n---待办任务统计信息---\n";
	std::cout << "任务总数: " << tasks.size() << std::endl;
	std::cout << "存储文件：" << getFilename() << std::endl;
	std::cout << "是否为空：" << (isEmpty() ? "是" : "否") << std::endl;

	if (!isEmpty()) {
		std::cout << "前三个任务：" << std::endl;
		int displayCount = std::min(3, static_cast<int>(tasks.size()));
		for (int i = 0; i < displayCount; ++i) {
			std::cout << " " << i << getTask(i ) << std::endl;
		}
	}
}

//私有方法：检查索引是否有效
bool Todolist::isValidIndex(int index) const {
	return (index>= 1 && index <= static_cast<int>(tasks.size()));
}

//私有方法:内部显示任务列表
void Todolist::displayTasksInternal() const {
	for (size_t i = 0; i < tasks.size(); ++i) {
		std::cout << " " << (i + 1) << ". " << tasks[i] << std::endl;
	}
}