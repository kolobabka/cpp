#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <array>

int main() {
  std::vector Array{1, 1, 2, 3, 4, 4, 3, 7, 8, 9, 10};

  std::cout << "Array :" << std::endl;
  std::copy(Array.cbegin(), Array.cend(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::cout << "Number of '1' :" << std::endl;
  std::cout << std::count(Array.begin(), Array.end(), 1) << std::endl;

  std::vector Array2{1, 1, 2, 3, 4, 4, 4, 7, 8, 9, 10};

  std::cout << "Array2 :" << std::endl;
  std::copy(Array2.cbegin(), Array2.cend(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::cout << "First mismatch :" << std::endl;

  auto [MismatchFirst, MismatchSecond] = std::mismatch(Array.begin(), Array.end(), Array2.begin());
  std::cout << "\tArray : " << *MismatchFirst << std::endl <<
               "\tArray2 : " << *MismatchSecond << std::endl;

  std::vector Array3{1, 1, 2, 3, 4, 4, 3, 7, 8, 9, 10};

  std::cout << "Array3 :" << std::endl;
  std::copy(Array3.cbegin(), Array3.cend(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::cout << "Check Array is equal Array3 : " <<
        std::equal(Array.begin(), Array.end(), Array3.begin()) << std::endl;

  std::cout << "Search subrange [3, 7, 8] in Array" << std::endl;

  auto SubArray = {3, 7, 8};
  auto Pos = std::search(Array.begin(), Array.end(), SubArray.begin(), SubArray.end());
  std::cout << "Position : " << std::distance(Array.begin(), Pos) << std::endl;


  std::cout << "Replace 3 with 4 in Array" << std::endl;
  std::replace(Array.begin(), Array.end(), 3, 4);

  std::cout << "Array :" << std::endl;
  std::copy(Array.cbegin(), Array.cend(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::cout << "Remove all 4 from Array" << std::endl;
  auto It = std::remove(Array.begin(), Array.end(), 4);
  Array.erase(It, Array.end());

  std::cout << "Array :" << std::endl;
  std::copy(Array.cbegin(), Array.cend(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::cout << "Make numbers in Array unique" << std::endl;

  It = std::unique(Array.begin(), Array.end());
  Array.erase(It, Array.end());

  std::cout << "Array :" << std::endl;
  std::copy(Array.cbegin(), Array.cend(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::cout << "Simple simple rotation to the left in Array" << std::endl;
  std::rotate(Array.begin(), Array.begin() + 1, Array.end());

  It = std::partition(Array.begin(), Array.end(), [](auto Num) {return Num & 1;});

  std::cout << "Partitioned Array :" << std::endl;
  std::copy(std::begin(Array), It, std::ostream_iterator<int>(std::cout, " "));
  std::cout << "* ";
  std::copy(It, std::end(Array), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}
