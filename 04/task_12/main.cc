#include <iostream>
#include <type_traits>
 
template<class T> struct add_const { typedef const T type; };

template<class T>
using add_const_t = typename add_const<T>::type;

template<class T> struct remove_const { typedef T type; };
template<class T> struct remove_const<const T> { typedef T type; };

template<class T>
using remove_const_t = typename remove_const<T>::type;

int main() {
   static_assert(std::is_same_v<int, remove_const_t<const int>>);
   static_assert(std::is_same_v<const int, add_const_t<int>>);

   std::cout << "Everything is ok!" << std::endl;
}