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
	std::cout << "TASK begin\n";
	(*f)(params);
	std::cout << "TASK end\n";
	return NULL;
}
