#include <type_traits>
#include <cstddef>

struct Impl;

struct FastPImpl {
    FastPImpl();
    ~FastPImpl();

    std::aligned_storage_t<32, alignof(std::max_align_t)> Storage;
    
    Impl* Handle;

    void doSomething();
};
