#pragma once
#include <iostream>
#include <fstream>
#include "Task.h";
#include "Colours.h"
using namespace std;

class System_Manager
{
private:
	// use of vector to preserve task order (instead of an unordered map)
	vector<Task> taskList;


public:
	void add_task(Task& t);
	void view_tasks();
	vector<int> searchTaskByName(string name);
	void edit_task(int, int, string);
	void delete_task(int);
	void mark_task_complete(int);

	Task& getTask(int i);

	void saveToFile(const string& filename);
	void loadFromFile(const string& filename);
};

