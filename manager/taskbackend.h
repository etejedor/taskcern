/*
 * TaskManagerData.h
 *
 *  Created on: Dec 30, 2014
 *      Author: etejedor
 */

#ifndef MANAGER_TASKDATA_
#define MANAGER_TASKDATA_

#include "tbb/task.h"
#include "taskmanager.h"

namespace cern_parallel {

class TaskData {
friend class TaskManager;
private:
	tbb::task* parent;
public:
	TaskData() {
		parent = new( tbb::task::allocate_root() ) tbb::empty_task;
		parent->increment_ref_count();
	}
	~TaskData() {
		parent->destroy(*parent);
	}
};


class Task : public tbb::task {
private:
	void hello();
public:
	Task() : tbb::task() { }
	tbb::task* execute();
};


} /* namespace cern_parallel */


#endif /* MANAGER_TASKDATA_ */
