#ifndef TODO_MANAGER_H
#define TODO_MANAGER_H

#include "Todolist.h"
#include <memory>

class TodoManager
{
	private:
		std::unique_ptr<Todolist> todoList;
		void printMainMenu() const;
		void printFileMenu() const;
		void handleMainMenu();
		void handleFileMenu();
		void handleAddTask();
		void handleDeleteTask();
		void handleSaveToFile();
		void handleLoadFromFile();
		void handleViewFileCountent() const;
public:
	TodoManager();
	void run();

};
#endif // !TODO_MANAGER_H
