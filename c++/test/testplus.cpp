
#include <unistd.h>
#include <iostream>
#include <sstream>

#include "taskplus.h"

void hello(const char* s, int i) {
	std::stringstream st;
	st << "Hello " << s << ", number " << i << std::endl;
	std::cout << st.str();

	sleep(1);
}


using namespace cern_parallel;

int main() {
    TaskManager tm;

    for (int i = 0; i < 10; i++) {
    	tm.add_task([=]{ hello("World", i); });
    }

    tm.wait();

    for (int i = 0; i < 10; i++) {
        tm.add_task([=]{ hello("World", i); });
    }
    tm.wait();
}



// TODO: fer exemple amb functor (mirar sudoku.cpp)
// TODO: fer parallel_for (es pot fer alhora amb tasques normals?
