#include <iostream>
#include <iterator>

class OddIterator {
    int Val;   
public:
    OddIterator(int InitVal = 1) : Val(InitVal) {
        if ((Val % 2) == 0)
            throw std::runtime_error("Initial value must be odd!");
    }
    using value_type = int;
    using difference_type = int;
    
    int operator* () const { return Val; }
    
    OddIterator &operator++() {
        Val += 2;   
        return *this;
    }
    
    OddIterator operator++(int) {
        auto OldVal = *this;
        ++*this;
        return OldVal;
    }

    bool equals(const OddIterator &Rhs) const { return Val == Rhs.Val; }
};

static bool operator==(OddIterator Lhs, OddIterator Rhs) {
  return Lhs.equals(Rhs);
}
static bool operator!=(OddIterator Lhs, OddIterator Rhs) {
  return !(Lhs == Rhs);
}

static_assert(std::forward_iterator<OddIterator>);

static constexpr int N = 10;

int main() {
  OddIterator OI;
  auto CI = std::counted_iterator{OI, N};
  for (auto It = CI; It != std::default_sentinel; ++It) {
    std::cout << *It << std::endl;
  }
}