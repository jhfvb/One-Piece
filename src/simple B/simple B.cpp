#include <iostream>
#include <vector>
#include <string>
#include <fstream>  // 新增：文件操作
#include <limits>

// 函数声明
void printMenu();
void addTask(std::vector<std::string>& tasks);
void viewTasks(const std::vector<std::string>& tasks);
void deleteTask(std::vector<std::string>& tasks);
void saveTasksToFile(const std::vector<std::string>& tasks, const std::string& filename); // 新增：保存到文件
void loadTasksFromFile(std::vector<std::string>& tasks, const std::string& filename);    // 新增：从文件加载
void showFileMenu(); // 新增：文件操作菜单

int main() {
    std::vector<std::string> tasks;
    int choice = 0;
    const std::string filename = "todo_list.txt"; // 定义保存的文件名

    std::cout << "=== 简易待办事项列表（文件存储版） ===" << std::endl;

    // 程序启动时自动尝试加载之前的任务
    std::cout << "正在从文件加载之前的任务..." << std::endl;
    loadTasksFromFile(tasks, filename);
    if (!tasks.empty()) {
        std::cout << "成功加载 " << tasks.size() << " 个任务！" << std::endl;
    }

    do {
        printMenu();
        std::cin >> choice;
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
            showFileMenu();
            break;
        case 5:
            std::cout << "感谢使用待办事项列表，再见！" << std::endl;
            break;
        default:
            std::cout << "无效选择，请重试。" << std::endl;
        }
    } while (choice != 5);

    return 0;
}

// 打印主菜单
void printMenu() {
    std::cout << "\n--- 主菜单 ---" << std::endl;
    std::cout << "1. 添加任务" << std::endl;
    std::cout << "2. 查看所有任务" << std::endl;
    std::cout << "3. 删除任务" << std::endl;
    std::cout << "4. 文件操作" << std::endl;  // 新增：文件操作菜单
    std::cout << "5. 退出程序" << std::endl;
    std::cout << "请选择操作 (1-5): ";
}

// 新增：文件操作菜单
void showFileMenu() {
    std::vector<std::string> tasks;
    const std::string filename = "todo_list.txt";
    int fileChoice = 0;

    do {
        std::cout << "\n--- 文件操作 ---" << std::endl;
        std::cout << "1. 保存任务到文件" << std::endl;
        std::cout << "2. 从文件加载任务" << std::endl;
        std::cout << "3. 查看文件内容" << std::endl;
        std::cout << "4. 返回主菜单" << std::endl;
        std::cout << "请选择操作 (1-4): ";

        std::cin >> fileChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (fileChoice) {
        case 1:
            saveTasksToFile(tasks, filename);
            break;
        case 2:
            loadTasksFromFile(tasks, filename);
            break;
        case 3:
        {
            std::ifstream file(filename);
            if (file.is_open()) {
                std::cout << "\n--- 文件内容 ---" << std::endl;
                std::string line;
                int lineNum = 1;
                while (std::getline(file, line)) {
                    std::cout << lineNum << ". " << line << std::endl;
                    lineNum++;
                }
                file.close();
            }
            else {
                std::cout << "文件不存在或无法打开！" << std::endl;
            }
        }
        break;
        case 4:
            std::cout << "返回主菜单..." << std::endl;
            break;
        default:
            std::cout << "无效选择，请重试。" << std::endl;
        }
    } while (fileChoice != 4);
}

// 添加新任务
void addTask(std::vector<std::string>& tasks) {
    std::string task;
    std::cout << "请输入新任务: ";
    std::getline(std::cin, task);

    if (!task.empty()) {
        tasks.push_back(task);
        std::cout << "任务添加成功！" << std::endl;

        // 自动保存到文件（可选功能）
        char autoSave;
        std::cout << "是否立即保存到文件？(y/n): ";
        std::cin >> autoSave;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (autoSave == 'y' || autoSave == 'Y') {
            saveTasksToFile(tasks, "todo_list.txt");
        }
    }
    else {
        std::cout << "任务内容不能为空！" << std::endl;
    }
}

// 查看所有任务
void viewTasks(const std::vector<std::string>& tasks) {
    if (tasks.empty()) {
        std::cout << "当前没有待办任务。" << std::endl;
        return;
    }

    std::cout << "\n--- 当前待办事项 ---" << std::endl;
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". " << tasks[i] << std::endl;
    }
    std::cout << "总计: " << tasks.size() << " 个任务" << std::endl;
}

// 删除任务
void deleteTask(std::vector<std::string>& tasks) {
    if (tasks.empty()) {
        std::cout << "当前没有可删除的任务。" << std::endl;
        return;
    }

    viewTasks(tasks);

    int taskNumber;
    std::cout << "请输入要删除的任务编号: ";
    std::cin >> taskNumber;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "请输入有效的数字！" << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (taskNumber >= 1 && taskNumber <= static_cast<int>(tasks.size())) {
        std::string removedTask = tasks[taskNumber - 1];
        tasks.erase(tasks.begin() + taskNumber - 1);
        std::cout << "任务 \"" << removedTask << "\" 已删除！" << std::endl;
    }
    else {
        std::cout << "无效的任务编号！" << std::endl;
    }
}

// 新增：保存任务到文件
void saveTasksToFile(const std::vector<std::string>& tasks, const std::string& filename) {
    std::ofstream outputFile(filename); // 创建输出文件流

    if (!outputFile.is_open()) {
        std::cout << "错误：无法创建或打开文件 " << filename << "！" << std::endl;
        return;
    }

    // 将每个任务写入文件，每行一个任务
    for (const auto& task : tasks) {
        outputFile << task << std::endl;
    }

    outputFile.close(); // 关闭文件
    std::cout << "成功保存 " << tasks.size() << " 个任务到文件: " << filename << std::endl;
}

// 新增：从文件加载任务
void loadTasksFromFile(std::vector<std::string>& tasks, const std::string& filename) {
    std::ifstream inputFile(filename); // 创建输入文件流

    if (!inputFile.is_open()) {
        std::cout << "文件 " << filename << " 不存在或无法打开，将创建新文件。" << std::endl;
        return;
    }

    tasks.clear(); // 清空当前任务列表
    std::string line;
    int loadedCount = 0;

    // 逐行读取文件内容
    while (std::getline(inputFile, line)) {
        if (!line.empty()) { // 忽略空行
            tasks.push_back(line);
            loadedCount++;
        }
    }

    inputFile.close(); // 关闭文件
    std::cout << "从文件加载了 " << loadedCount << " 个任务。" << std::endl;
}