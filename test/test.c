
#include <stdio.h>
#include "task.h"


// ORIGINAL METHOD

void hello(char* s, int i) {
	printf("Hello %s, number %d\n", s, i);
	sleep(5);
}

// WRAPPERS

struct hello_params {
	char* s;
	int i;
};

void hello_task(void* params) {
	struct hello_params* p = (struct hello_params*)params;
	hello(p->s, p->i);
}


// MAIN

int main(int argc, char* argv) {
    cern_init();

    struct hello_params hp = { "World", 1 };
    cern_add_task(&hello_task, &hp);

    cern_wait();

    cern_end();

    return 0;
}


//void (*lala)(int) = &hello;

//(*lala)(1);


//struct {
//	int i;
//} argsTask1;
//
//
//void wrapperTask1 (void * args);
//
//void wraperTask1 (void * args)
//{
//	struct argsTask1 * argsT1 = args;
//
//	task1(argsT1->i);
//}



//void (*wrapper1)(void *) = &wrapperTask1;
//
//// Option A:
//struct argsTask1 args;
//args.i = 3;
//
//// Option B:
//struct argsTask1 *args2 = (struct argsTask1 *) malloc(sizeof(struct argsTask1));
//args2->i = 3;
//
//
//(*wrapper1)(&args);
//(*wrapper1)(args2);
