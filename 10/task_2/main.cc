#include <iostream>
#include <vector>
#include <exception>

static constexpr auto NumElts = 50000000u;

void fillVectorTrivially() {
    std::vector<int> Vec;
    auto CurCap = Vec.capacity();

    std::cout << "Initial cap : " << CurCap << std::endl;

    // We expects capacity increases in some way: f.e double each time
    // when size = capacity / 2
    // Note: we are promised to have an amortized O(1). It's not a mandatory 
    // requirement to twice a capacity
    for (auto I = 0u; I < NumElts; ++I) {
        Vec.push_back(I);
        if (CurCap != Vec.capacity()) {
            std::cout << "I : " << I << ";";
            CurCap = Vec.capacity();
            std::cout << "\tNew cap : " << CurCap << std::endl;
        }
    }
}

void fillVectorWithReserve() {
    std::vector<int> Vec;
    std::cout << "Reserve with " << NumElts << "..." << std::endl;
    Vec.reserve(NumElts);

    auto CurCap = Vec.capacity();

    // In this case we want not to see any relocations 
    std::cout << "Initial cap : " << CurCap << std::endl;

    for (auto I = 0u; I < NumElts; ++I) {
        Vec.push_back(I);
        if (CurCap != Vec.capacity()) {
            std::cout << "I : " << I << ";";
            CurCap = Vec.capacity();
            std::cout << "\tNew cap : " << CurCap << std::endl;
        }
    }
}

void fillVectorWithExhausted() {
    std::vector<int> Vec;
    std::cout << "Reserve with " << NumElts << "..." << std::endl;
    Vec.reserve(NumElts);
    
    auto CurCap = Vec.capacity();

    std::cout << "Initial cap : " << CurCap << std::endl;

    // In this case we try to exhaust memory for target machine 
    // It's expected to catch a bad_alloc 
    try {
        while (true)
            Vec.push_back(42);
        // dummy dump to add an observable behaviour for infinite loop
        std::cout << Vec.size() << "\n"; 
    } catch (std::bad_alloc &Err) {
        std::cout << Err.what() << "\n";
    }
}

int main() { 
    fillVectorTrivially();
    fillVectorWithReserve();
    fillVectorWithExhausted();
}