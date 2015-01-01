#include "task.h"

int main() {

    cern_init();
    cern_addTask();
    cern_addTask();
    cern_addTask();
    cern_addTask();
    cern_addTask();
    cern_addTask();
    cern_addTask();
    cern_addTask();
    cern_addTask();
    cern_wait();
    cern_finalize();

    return 0;

}
