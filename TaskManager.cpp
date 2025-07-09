#include <iostream>
#include <vector>
#include <string>
#include "Task.h"
#include "System_Manager.h"
#include "Colours.h"
#include <windows.h>
using namespace std;

void enableVirtualTerminal() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
}
int validateInput(int, int);

int main()
{
	enableVirtualTerminal(); 
	System_Manager manager;
	manager.loadFromFile("tasks.txt"); 
	string task_name, task_desc, task_deadline; 

	int choice;
	do {
		cout << BOLD << CYAN << "\n===============================   Task Manager   ===============================\n" << RESET 
			<< YELLOW <<
			"Enter a choice: \n" << "[1] Add Task \n" <<
			"[2] Edit Task \n" << "[3] Delete Task \n" <<
			"[4] Mark Task as Completed \n" << "[5] View Tasks \n"
			"[6] Exit program \n" << RESET;
		
		choice = validateInput(1, 6);
		cout << "\n = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n";

		switch (choice) {
		case 1:
		{
			cout << BOLD << "Enter task name: \n" << RESET; 
			cin.ignore();
			getline(cin, task_name);
			cout << BOLD << "Enter task description: \n" << RESET; 
			getline(cin, task_desc);
			cout << BOLD << "Enter task deadline: \n" << RESET; 
			getline(cin, task_deadline);
			Task t(task_name, task_desc, task_deadline);

			// a separate function is used to allow for scalability in the future
			manager.add_task(t);
			manager.saveToFile("tasks.txt"); 
			cout << "\n = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n";
			break;
		}
		case 2:
		{
			cout << BOLD << "Enter the task name you wish to edit: " << RESET;
			cin.ignore();
			getline(cin, task_name);

			vector<int> matchedTasks = manager.searchTaskByName(task_name);
			if (matchedTasks.empty()) {
				cout << RED << "There are no tasks available! \n" << RESET;
				break;
			}

			cout << BOLD << "Enter the number of the task you want to edit: " << RESET;
			int option;
			cin >> option;
			if (cin.fail()) {  // avoiding char errors
				cin.clear();
				cin.ignore(10000, '\n');
				choice = -1;
			}

			while (option ==-1) {
				cout << RED << "Invalid choice! Please try again. \n" << RESET;
				cin >> option;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(10000, '\n');
					option = -1;
				}
			}

			int index = matchedTasks[option - 1];
			cout << BOLD << "What would you like to edit? " << RESET<<
				YELLOW << "\n[1] Task Name \n" <<
				"[2] Task Description \n" << "[3] Task Deadline \n" << RESET;
			cout << BOLD << "Enter your choice: " << RESET;
			option = validateInput(1, 3);

			string userInput;
			switch (option) {
			case 1:
			{
				cout << BOLD << "Enter new task name: \n" << RESET;
				cin.ignore();
				getline(cin, userInput);
				break;
			}
			case 2:
			{
				cout << BOLD << "Enter the new task description: \n" << RESET;
				cin.ignore();
				getline(cin, userInput);
				break;
			}
			case 3:
			{
				cout << BOLD << "Enter the new task deadline: \n" << RESET;
				cin.ignore();
				getline(cin, userInput);
				break;
			}
			default:
				cout << RED << "Invalid input! \n" << RESET;
			}

			manager.edit_task(index, option, userInput);
			manager.saveToFile("tasks.txt");   
			cout << "\n = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n";
			break;
		}
		case 3:
		{
			cout << BOLD << "Enter the task name you wish to delete: " << RESET;
			cin.ignore();
			getline(cin, task_name);

			vector<int> matchedTasks = manager.searchTaskByName(task_name);
			if (matchedTasks.empty()) {
				cout << RED << "There are no tasks available! \n" << RESET;
				break;
			}

			cout << BOLD << "Enter the number of the task you want to delete: " << RESET;
			int option;
			cin >> option;
			if (cin.fail()) {  
				cin.clear();
				cin.ignore(10000, '\n');
				choice = -1;
			}

			while (option == -1) {
				cout << RED << "Invalid choice! Please try again. \n" << RESET;
				cin >> option;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(10000, '\n');
					option = -1;
				}
			}

			int index = matchedTasks[option - 1];
			manager.delete_task(index);
			manager.saveToFile("tasks.txt");    
			cout << "\n = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n";
			break;
		}
		case 4: 
		{
			cout << BOLD << "Enter the name of the task you want to mark as complete: " << RESET;
			cin.ignore();
			getline(cin, task_name);

			vector<int>matchedTasks = manager.searchTaskByName(task_name);
			if (matchedTasks.empty()) {
				cout << RED << "No matching tasks found. \n" << RESET;
				break;
			}

			cout << BOLD << "Enter the number of the task to mark as complete: " << RESET;
			int option = validateInput(1, matchedTasks.size());

			int index = matchedTasks[option - 1];
			manager.mark_task_complete(index);
			manager.saveToFile("tasks.txt");  
			cout << "\n = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n";
			break;
		}
		case 5:
		{
			manager.view_tasks();
			break;
		}
		}
	} while (choice != 6);

	return 0;
}

int validateInput(int lowerBound, int upperBound) {
	int userInput;
	cin >> userInput;
	
	if (cin.fail()) {  
		cin.clear();
		cin.ignore(10000, '\n');
		userInput = -1;
	}

	while (userInput < lowerBound || userInput > upperBound) {
		cout << RED << "Invalid choice! Value must be between " << 
			lowerBound << " and " << upperBound << 
			", please try again. \n" << RESET;
		cin >> userInput;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			userInput = -1;
		}
	}

	return userInput;
}