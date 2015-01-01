/*
 * taskmanager.h
 *
 *  Created on: Dec 24, 2014
 *      Author: etejedor
 */

#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_


namespace cern_parallel {

class TaskData;

class TaskManager {
private:
	TaskData* data;
public:
	TaskManager();
	~TaskManager();
	void addTask();
	void wait();

};

}

#endif /* TASKMANAGER_H_ */
