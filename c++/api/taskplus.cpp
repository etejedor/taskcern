/*
 * parallel.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: etejedor
 */


#include "taskplus.h"

using namespace cern_parallel;

void TaskManager::wait() {
	std::cout << "WAITING\n";
	g.wait();
	std::cout << "End of WAIT\n";
}
