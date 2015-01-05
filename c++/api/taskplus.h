/*
 * task.h
 *
 *  Created on: Dec 24, 2014
 *      Author: etejedor
 */

#ifndef TASK_H_
#define TASK_H_

#include <iostream>

#include "tbb/task_group.h"

namespace cern_parallel {

class TaskManager {
private:
	tbb::task_group g;
public:
	TaskManager() {}
	~TaskManager() {}

	template<typename F>
	void add_task(const F& f) {
		g.run(f);
		std::cout << "Spawned" << std::endl;
	}

	void wait();
};

}

#endif /* TASK_H_ */
