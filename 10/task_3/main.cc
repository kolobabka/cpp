#include <algorithm> 
#include <cassert>
#include <iterator>
#include <iostream>
#include <forward_list>
#include <numeric>

static constexpr auto NumElts = 100u;

int main() { 
    std::forward_list<int> List(NumElts);
    // Initialize the list with iota range
    std::iota(List.begin(), List.end(), 0);

    std::copy(List.begin(), List.end(), std::ostream_iterator<int>( std::cout, " "));
    std::cout << std::endl;

    // The algo idea: we have fast and slow pointers: the first one steps 
    // through 2 elements, the second one through 1. When the the fast pointer
    // reaches List.end(), the slow one points to the list middle 
    // if list.size() is even and [last - first] / 2 + 1 otherwise
    auto ItTortoise = List.begin();
    for (auto ItHare = ItTortoise; ItHare != List.end(); ItHare = std::next(ItHare, 2)) {
        ++ItTortoise;
    }

    assert(List.size());
    std::cout << *ItTortoise << std::endl;
}