/*
 * parallel.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: etejedor
 */


#include <cstddef>
#include "task.h"
#include "taskmanager.h"

#ifdef __cplusplus
using namespace cern_parallel;
#endif

static TaskManager *mng = NULL;

void cern_init() {
	if (mng == NULL)
		mng = new TaskManager();
}

void cern_add_task(void (*f)(void*), void* params) {
	mng->addTask(f, params);
}

void cern_wait() {
	mng->wait();
}

void cern_end() {
	delete mng;
}
