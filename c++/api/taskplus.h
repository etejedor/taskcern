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
#include "tbb/task_scheduler_init.h"

namespace cern_parallel {

class TaskManager {
private:
	tbb::task_scheduler_init init;
	tbb::task_group g;
public:
	TaskManager() {}
	TaskManager(int numthreads) : init(numthreads), g() { }
	~TaskManager() {}

	template<typename F>
	void add_task(const F& f) {
		g.run(f);
		//std::cout << "Spawned" << std::endl;
	}

	template <typename Index, typename Function>
	void parallel_for(Index first, Index last, const Function& f) {
		//tbb::task_scheduler_init init(1);
	    tbb::parallel_for(first, last, f);
	}

	template <typename Index, typename Function>
	void parallel_for(Index first, Index last, Index step, const Function& f) {
		//int n = tbb::task_scheduler_init::default_num_threads();
		//std::cout << "Num threads " << n << std::endl;
		tbb::parallel_for(first, last, step, f);
	}

	void wait();
};

}

#endif /* TASK_H_ */
