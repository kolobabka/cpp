#include <iostream>

template<typename T> 
int sum(T arg) {
    if constexpr(std::is_same_v<T, int>)
        return arg;
    else 
        return 0;
}

template<typename T, typename ...Args> 
int sum(T arg, Args... args) {
    if constexpr(std::is_same_v<T, int>)
        return arg + sum(args ...);
    else 
        return sum(args ...);
}

struct Dummy {};

int main() {
    std::cout << sum('c', 1, 2, 4.2, 3, "asad", 4, 5, "asad") << std::endl; // 15
    std::cout << sum(Dummy{}, 4.2, "asad") << std::endl; // 0
}