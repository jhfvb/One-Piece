#ifndef TODOLIST_H
#define TODOLIST_H

#include <vector>
#include <string>
#include <fstream>
class Todolist {
private:
	std::vector<std::string> tasks;
	std::string filename;

	//私有辅助方法
	bool isValidIndex(int index) const;
	void displayTasksInternal() const;

public:
	//构造函数
	Todolist();
	explicit Todolist(const std::string& file);

	//核心功能方法
	void addTask(const std::string& task);
	void viewTasks() const;
	void deleteTask(int taskNumber);
	void clearAllTasks();

	//文件操作方法
	bool saveToFile() const;
	bool loadFromFile();
	bool saveToFile(const std::string& file) const;
	bool loadFromFile(const std::string& file);

	//查询方法
	int getTaskCount() const;
	bool isEmpty() const;
	std::string getTask(int index) const;

	//状态信息
	std::string getFilename() const;
	void setFilename(const std::string& newFilename);

	//工具方法
	void displayStatistics() const;
};

#endif // !TODOLIST_H

