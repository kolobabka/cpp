#include <iostream>
#include <type_traits>
		
template<size_t N> 
struct Fact : std::integral_constant<size_t, N * Fact<N - 1>{}> {};

template<> struct Fact<0> : std::integral_constant<size_t, 1> {};

template<size_t N, size_t K> 
struct Binom : std::integral_constant<size_t, Fact<N>{} / (Fact<K>{} * Fact<N-K>{})> {};


int main() {
    std::cout << Binom<0, 0>::value << std::endl; // 1
    std::cout << Binom<1, 1>::value << std::endl; // 1
    std::cout << Binom<5, 3>::value << std::endl; // 10
    std::cout << Binom<4, 2>::value << std::endl; // 6
}