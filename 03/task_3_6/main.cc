#include <iostream>
#include <cassert>

#include "Container.hpp"

int main() {
    MyVector::Container my_vector(2);
    my_vector.push_back(1);
    my_vector.push_back(2);
    my_vector.push_back(3);
    my_vector.push_back(4);
    my_vector.push_back(5);
    my_vector.push_back(6);

    std::cout << my_vector.size() << std::endl;
    std::cout << my_vector.capacity() << std::endl;

    MyVector::Container my_vector_2(10);

    for (int i = 0; i < my_vector.size(); i++) {
        printf("my_vector[%d] = %d\n", i, my_vector[i]);
    }

    my_vector_2 = std::move(my_vector);
    for (int i = 0; i < my_vector_2.size(); i++) {
        printf("my_vector_2[%d] = %d\n", i, my_vector_2[i]);
    }

    assert(my_vector_2.back() == 6);

    // Empty container - good
    MyVector::Container arr;
    arr.push_back(42);
    assert(arr[0] == 42);
    assert(arr.size() == 1);
    assert(arr.capacity() >= 1);

    return 0;
}
