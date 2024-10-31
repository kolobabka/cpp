#include <iostream>

namespace detail {
    template<typename T>
    std::integral_constant<bool, !std::is_union<T>::value> test(int T::*);
 
    template<typename>
    std::false_type test(...);
}
 
template<typename T>
struct is_class : decltype(detail::test<T>(nullptr)) {};

template<typename T>
constexpr bool is_class_v = is_class<T>::value;

namespace {
struct S {
    int x;
};

union U {
    int x;
};
}

int main() {
   static_assert(is_class_v<S>);
   static_assert(!is_class_v<U>);

   std::cout << "Everything is ok!" << std::endl;
}