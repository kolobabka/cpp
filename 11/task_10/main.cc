#include <iostream>
#include <cassert>
#include <vector>

#include "my_std.h"

int main() {
  std::vector Vec{1, 2, 3, 4, 5, 6};

  assert(my_std::any_of(Vec, 4, 2));
  assert(!my_std::any_of(Vec, 7, 8, 9, 10));
  
  assert(my_std::all_of(Vec, 1, 2, 3, 4, 5, 6));
  assert(!my_std::all_of(Vec, 1, 2, 3, 4, 5, 6, 7));
  
  assert(my_std::none_of(Vec, 7, 8, 9, 10));
  assert(!my_std::none_of(Vec, 7, 8, 9, 10, 1));
}
