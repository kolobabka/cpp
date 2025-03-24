#include <iostream>
#include <cassert>
#include <iterator>
#include <vector>

#include "my_std.h"

int main() {
  std::vector Vec{1, 2, 3, 4, 5, 6};

  std::vector<int> DstVec;

  my_std::transform_if(Vec.begin(), Vec.end(), std::back_inserter(DstVec), [](const auto &Num) { return Num * Num;}, [](const auto &Num){ return Num & 1;});

  std::copy(DstVec.begin(), DstVec.end(), std::ostream_iterator<int>(std::cout, " "));
}
