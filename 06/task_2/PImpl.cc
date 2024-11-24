#include "PImpl.h"

#include <iostream>
#include <memory>

struct Impl {
  void doSomething() {
    std::cout << "Hello, I'm Impl!\n";
  }
};

void DefaultDeleter::operator()(Impl *I) {
  std::default_delete<Impl>{}(I);
}

PImpl::PImpl() : I(std::unique_ptr<Impl, DefaultDeleter>()) {}

void PImpl::doSomething() {
  I->doSomething();
}

int main() {
  PImpl PI;
  PI.doSomething();
}
