#include <memory>

struct Impl;

struct DefaultDeleter {
  void operator()(Impl *);
};

class PImpl { 
  std::unique_ptr<Impl, DefaultDeleter> I;

public:
  PImpl();

  void doSomething();
};
