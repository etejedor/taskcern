/*
 * taskmanager.cpp
 *
 *  Created on: Dec 24, 2014
 *      Author: etejedor
 */

#include <unistd.h>
#include <iostream>
#include "taskmanager.h"
#include "taskbackend.h"

// using namespace std;

using namespace cern_parallel;

TaskManager::TaskManager() {
	data = new TaskData();
}

TaskManager::~TaskManager() {
	delete data;
}

void TaskManager::addTask() {
	tbb::task& tk = *new( data->parent->allocate_child() ) Task;
	data->parent->increment_ref_count();
	data->parent->spawn(tk);
	std::cout << "Added\n";
}

void TaskManager::wait() {
	data->parent->wait_for_all();
}

//
//int * p;
//
//int i;
//
//*p = i;
//
//myclass o;
//
//o.func();
//
//f1(&o);
//f2(o);
//f3(o);
//
//
//
//void f1 (myclass* o) {}
//void f2 (myclass o) {}
//void f3 (myclass& o) {}


