#include <iostream>
#include <type_traits>

// Suppose all arguments are integer type
template<typename T>
concept IsInt = requires {
    typename std::enable_if_t<std::is_integral<T>::value>;
};

template<typename T> requires IsInt<T> 
int min(T arg) {
    return arg;
}

template<typename T, typename ...Args> requires IsInt<T>
int min(T arg, Args... args) {
    return std::min(arg, min(args...));
}


int main() {
    std::cout << min(5, 7, 9, 2, 1, 2, 3) << std::endl; // 1
}