#include "FastPImpl.h"

#include <iostream>

struct Impl {
  void doSomething() {
    std::cout << "Hello! I'm FastPImpl idiom\n";
  }
};

FastPImpl::FastPImpl() {
    static_assert(sizeof(Impl) <= sizeof(Storage) , "Object can't fit into local storage");
    Handle = new (&Storage) Impl();
}

FastPImpl::~FastPImpl() {
    Handle->~Impl();
}

void FastPImpl::doSomething() {
  Handle->doSomething();
}

int main() {
  FastPImpl FPI;
  FPI.doSomething();
}
