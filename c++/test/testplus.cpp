
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

class HelloFunctor {
    const char* s;
    int i;
public:
    HelloFunctor(const char* ss, int ii) : s(ss), i(ii) {}
    void operator()() const {
    	hello(s, i);
    }
};


using namespace cern_parallel;

int main() {
    TaskManager tm;

    // Lambda expression
    for (int i = 0; i < 10; i++) {
    	tm.add_task([=]{ hello("Lambda", i); });
    }
    tm.wait();

    // Functor
    for (int i = 0; i < 10; i++) {
        tm.add_task(HelloFunctor("Functor", i));
    }
    tm.wait();

    // Parallel for
    tm.parallel_for(0, 10, [=](int i){ hello("Parallel_for", i); });
}
