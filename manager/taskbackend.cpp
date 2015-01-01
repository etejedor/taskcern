/*
 * taskbackend.cpp
 *
 *  Created on: Dec 30, 2014
 *      Author: etejedor
 */

#include <iostream>
#include "taskbackend.h"

using namespace cern_parallel;

tbb::task* Task::execute() {
	hello();
	std::cout << "Exiting task\n";
	return NULL;
}

void Task::hello() {
	std::cout << "HAllo\n";
	sleep(5);
}
