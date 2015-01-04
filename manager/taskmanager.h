/*
 * taskmanager.h
 *
 *  Created on: Dec 24, 2014
 *      Author: etejedor
 */

#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_


namespace cern_parallel {

class TaskManagerData;

class TaskManager {
private:
	TaskManagerData* data;
public:
	TaskManager();
	~TaskManager();
	void addTask(void (*)(void*), void*);
	void wait();
};

}

#endif /* TASKMANAGER_H_ */
