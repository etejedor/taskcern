/*
 * task.h
 *
 *  Created on: Dec 24, 2014
 *      Author: etejedor
 */

#ifndef TASK_H_
#define TASK_H_

#ifdef __cplusplus
extern "C" {
#endif

void cern_init();
void cern_addTask();
void cern_wait();
void cern_finalize();

#ifdef __cplusplus
}
#endif

#endif /* TASK_H_ */
