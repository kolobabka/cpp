#include <iostream>

template<class T>
struct decay {
private:
    typedef typename std::remove_reference<T>::type U;
public:
    typedef typename std::conditional< 
        std::is_array<U>::value,
        typename std::add_pointer<typename std::remove_extent<U>::type>::type,
        typename std::conditional< 
            std::is_function<U>::value,
            typename std::add_pointer<U>::type,
            typename std::remove_cv<U>::type
        >::type
    >::type type;
};

template<class T>
using decay_t = typename decay<T>::type;

int main() {
   static_assert(std::is_same_v<int, decay_t<int &>>);
   static_assert(std::is_same_v<int, decay_t<const int &>>);
   static_assert(std::is_same_v<int *, decay_t<int[5]>>);
   static_assert(std::is_same_v<const int *, decay_t<const int[5]>>);

   std::cout << "Everything is ok!" << std::endl;
}