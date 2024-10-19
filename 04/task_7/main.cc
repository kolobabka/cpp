#include <iostream>
#include <type_traits>
		
template<size_t N> 
struct Fib : std::integral_constant<size_t, Fib<N - 2>{} + Fib<N - 1>{}> {};

template<> struct Fib<0> : std::integral_constant<size_t, 0> {};
template<> struct Fib<1> : std::integral_constant<size_t, 1> {};

int main() {
    std::cout << Fib<0>::value << std::endl;
    std::cout << Fib<1>::value << std::endl;
    std::cout << Fib<2>::value << std::endl;
    std::cout << Fib<3>::value << std::endl;
    std::cout << Fib<4>::value << std::endl;
    std::cout << Fib<5>::value << std::endl;
    std::cout << Fib<6>::value << std::endl;
    std::cout << Fib<7>::value << std::endl;
    std::cout << Fib<8>::value << std::endl;
    std::cout << Fib<9>::value << std::endl;
    std::cout << Fib<10>::value << std::endl;
}