#include "ScopeGuard.h"

#include <cstdlib>
#include <exception>
#include <iostream>

int *dummyActionA() {
    return new int[5]{1, 2, 3, 4, 5};
}

void dummyActionB(bool CauseException) {
    if (CauseException)
        throw std::runtime_error("dummyActionB threw exception!");
}

void foo(int *& Ptr) {
    Ptr = dummyActionA();
    ScopeGuard SG([Ptr]() noexcept {delete [] Ptr; });
    dummyActionB(true);
    SG.disable();
}

int main() {
    try {
        int *Ptr;
        foo(Ptr);
        delete Ptr;
    } catch(std::runtime_error &Err) {
        std::cerr << Err.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}