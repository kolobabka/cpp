#include "Logger.h"

void bar() {
    logger::Logger bar_logger;
    logger::log("I'm bar()!");
}

void foo() {
    logger::Logger L;
    logger::log("Let's call for bar()");
    bar();
}

int main() { 
    foo();
}