
#include <unistd.h>
#include <iostream>
#include <sstream>

#include "taskplus.h"

void hello(const char* s, int i) {
	std::stringstream st;
	st << "Hello " << s << ", number " << i << std::endl;
	std::cout << st.str();

	sleep(2);
}


using namespace cern_parallel;

int main() {
    TaskManager tm;

    tm.add_task([=]{ hello("World", 1); });

    tm.wait();
}



// TODO: fer exemple amb functor (mirar sudoku.cpp)
// TODO: fer parallel_for
