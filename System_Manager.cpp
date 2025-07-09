#include <iostream>
#include <algorithm>
#include "System_Manager.h"
#include "Task.h"
using namespace std;

void System_Manager::add_task(Task& t) {
	for (auto task : taskList) {
		if (task.getTaskName() == t.getTaskName() &&
		task.getTaskDeadline() == t.getTaskDeadline() &&
		task.getTaskDesc() == t.getTaskDesc()) {
			cout << RED << "This task already exists! \n" << RESET;
			return;
		}
	}

	taskList.push_back(t);
	cout << GREEN << "Task added successfully! \n" << RESET;
}

void System_Manager::view_tasks() {
	for (int i = 0; i < taskList.size(); ++i) {
		cout << "\n[" << i + 1 << "] ";
		taskList[i].display();
		cout << endl;
	}
}

Task& System_Manager::getTask(int i) {
	return taskList[i];
}

// helper function, returns tasks whose names contain text entered by the user
vector<int> System_Manager::searchTaskByName(string name) {
	vector<int> matches;

	for (int i = 0; i < taskList.size(); ++i) {
		if (taskList[i].getTaskName().find(name) != string::npos) {
			matches.push_back(i);
		}
	}

	for (int j = 0; j < matches.size(); j++) {
		Task task = getTask(matches[j]);
		cout << "[" << j + 1 << "] " << BOLD << CYAN << task.getTaskName() << ", "
			<< "due on " << task.getTaskDeadline() << RESET << endl;
	}

	return matches;
}

void System_Manager::edit_task(int i, int j, string userInput) {
	if (i < 0 || i >= taskList.size()) {
		cout << RED << "Invalid index! \n" << RESET;
		return;
	}
	
	if (j == 1) {
		taskList[i].setTaskName(userInput);
	}
	else if (j == 2) {
		taskList[i].setTaskDescription(userInput);
	}
	else if (j == 3) {
		if (taskList[i].getTaskStatus()) {
			cout << RED << "You cannot change the deadline of a completed task! \n" << RESET;
			return;
		} 

		taskList[i].setTaskDeadline(userInput);
	}
	else {
		cout << RED << "Invalid choice! \n" << RESET;
	}
}

void System_Manager::delete_task(int i) {
	if (i < 0 || i >= taskList.size()) {
		cout << RED << "Invalid index! \n" << RESET;
		return;
	}

	taskList.erase(taskList.begin() + i);
	cout << GREEN << "Task deleted successfully! \n" << RESET;
}

void System_Manager::mark_task_complete(int i) {
	if (i < 0 || i >= taskList.size()) {
		cout << RED << "Invalid index! \n" << RESET;
		return;
	}

	taskList[i].mark_complete();
	cout << GREEN << "Task successfully marked as complete! \n" << RESET;
}

void System_Manager::saveToFile(const string& filename) {
	ofstream outFile(filename);
	for (const auto& task : taskList) {
		outFile << task.toString() << endl;
	}
	outFile.close();
}

void System_Manager::loadFromFile(const string& filename) {
	ifstream inFile(filename);
	string line;
	while (getline(inFile, line)) {
		Task t;
		t.fromString(line);
		taskList.push_back(t);
	}
	inFile.close();
}

