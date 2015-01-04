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
void cern_add_task(void (*)(void*), void*);
void cern_wait();
void cern_end();

#ifdef __cplusplus
}
#endif

#endif /* TASK_H_ */
