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
#include "tbb/parallel_for.h"

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
		//std::cout << "Spawned" << std::endl;
	}

	template <typename Index, typename Function>
	void parallel_for(Index first, Index last, const Function& f) {
	    tbb::parallel_for(first, last, f);
	}

	template <typename Index, typename Function>
	void parallel_for(Index first, Index last, Index step, const Function& f) {
		tbb::parallel_for(first, last, step, f);
	}

	void wait();
};

}

#endif /* TASK_H_ */
