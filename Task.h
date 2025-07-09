#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Task
{
private:
	string id;
	string task_name;
	string task_desc;
	string task_deadline;
	bool is_complete;
	static int task_count;

public:
	Task();
	Task(string task_name, string task_desc, string task_deadline);
	void display() const;

	string getId();
	string getTaskName();
	string getTaskDesc();
	string getTaskDeadline();
	bool getTaskStatus();

	void setTaskName(string);
	void setTaskDescription(string);
	void setTaskDeadline(string);
	void mark_complete();

	// file functions: 
	string toString() const;
	void fromString(const string&);
};

