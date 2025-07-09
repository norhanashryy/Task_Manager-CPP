#include "Task.h"
#include "Colours.h"

int Task::task_count = 0;
Task::Task() {
	task_name = "task " + id;
	task_desc = " - ";
	task_count++;
	id = to_string(task_count);
	task_deadline = "dd/mm/yyyy";
	is_complete = false;
}

Task::Task(string task_name, string task_desc, string task_deadline) : 
	task_name(task_name), task_desc(task_desc), 
	task_deadline(task_deadline), is_complete(false) {
	task_count++;
	id = to_string(task_count);
}

void Task::display() const{

	cout << CYAN << "Task ID: " << id << RESET << endl; 
	cout << CYAN << "Task name: " << task_name << RESET << endl; 
	cout << CYAN << "Task description: " << task_desc << RESET << endl;
	cout << CYAN << "Task deadline: " << task_deadline << RESET << endl;
	cout << CYAN << "Task Status: ";
	if (is_complete) {
		cout << GREEN << "Complete" << RESET << endl;
	}
	else {
		cout << RED << "Incomplete" << RESET << endl;
	}
}

void Task::mark_complete() {
	is_complete = true;
}

string Task::getId() {
	return id;
}

string Task::getTaskName() {
	return task_name;
}

string Task::getTaskDesc() {
	return task_desc;
}

string Task::getTaskDeadline() {
	return task_deadline;
}

bool Task::getTaskStatus() {
	return is_complete;
}

void Task::setTaskName(string task_name) {
	this->task_name = task_name;
}

void Task::setTaskDescription(string task_desc) {
	this->task_desc = task_desc;
}

void Task::setTaskDeadline(string task_deadline) {
	this->task_deadline = task_deadline;
}

string Task::toString() const {
	return id + "," + task_name + "," + task_desc + "," + task_deadline + "," + (is_complete ? "1" : "0");
}

void Task::fromString(const string& line) {
	stringstream ss(line);
	string token;
	getline(ss, id, ',');
	getline(ss, task_name, ',');
	getline(ss, task_desc, ',');
	getline(ss, task_deadline, ',');
	getline(ss, token, ',');
	is_complete = (token == "1");
}