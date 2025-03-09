#include <algorithm> 
#include <cassert>
#include <iterator>
#include <iostream>
#include <numeric>
#include <vector>
#include <set>

#include <random>
#include <string>
#include <functional>
#include <string_view>
namespace {

static constexpr auto StrsNumInit = 1000000u;
static constexpr auto StrsNumFin = 2000000u;
static constexpr auto Step = 100000u;
static constexpr auto NIters = (StrsNumFin - StrsNumInit) / Step; 

static constexpr auto StrLength = 10u;

std::string generateRandomString(std::mt19937 &Gen, std::uniform_int_distribution<char> &UD) {
    std::string RandomStr;
    for(unsigned I = 0; I < StrLength; ++I)
        RandomStr += UD(Gen);
    return RandomStr;
}

std::vector<std::string> getNRandomStrings(unsigned N, unsigned Seed = 0) {
    std::set<std::string> StringSet;
    std::mt19937 Gen(Seed);
    std::uniform_int_distribution<char> UD('a', 'z');
    
    while(StringSet.size() != N)
        StringSet.insert(generateRandomString(Gen, UD));

    std::vector<std::string> Vec(std::make_move_iterator(StringSet.begin()),
                                 std::make_move_iterator(StringSet.end()));

    return Vec;
}

unsigned RSHash(std::string_view Str) {
    static constexpr const unsigned A = 63689;

    return std::get<0>(std::accumulate(Str.begin(), Str.end(), 
    std::pair<unsigned, unsigned>{0, A}, 
    [](auto Acc, auto Sym) -> decltype(Acc) {
        static constexpr unsigned B = 378551;
        auto &&[Hash, NewA] = Acc;
        return {Hash * NewA + Sym, NewA * B};
    }));
}

unsigned JSHash(std::string_view Str) {
    static constexpr const unsigned Hash = 1315423911;

    return std::accumulate(Str.begin(), Str.end(), 
    Hash, [](auto Acc, auto Sym) {
        return Acc ^ ((Acc << 5) + Sym + (Acc >> 2));
    });
}

unsigned PJWHash(std::string_view Str) {
    return std::accumulate(Str.begin(), Str.end(), 
    0u, [](auto Acc, auto Sym) {
        static constexpr const unsigned BitsInUnsignedInt = 
                    static_cast<unsigned>(sizeof(unsigned) * 8);
        static constexpr const unsigned ThreeQuarters = 
                    static_cast<unsigned>((BitsInUnsignedInt  * 3) / 4);
        static constexpr const unsigned OneEighth = 
                    static_cast<unsigned>(BitsInUnsignedInt / 8);
        static constexpr const unsigned HighBits = 
                    static_cast<unsigned>(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);

        Acc = (Acc << OneEighth) + Sym;
        if (unsigned Test = Acc & HighBits)
            Acc = ((Acc ^ (Test >> ThreeQuarters)) & (~HighBits));
        return Acc;
    });
}

unsigned ELFHash(std::string_view Str) {
    return std::accumulate(Str.begin(), Str.end(), 
    0u, [](auto Acc, auto Sym) {
        Acc = (Acc << 4) + Sym;
        unsigned X = 0;
        if (X = Acc & 0xF0000000L)
            Acc ^= (X >> 24);

        Acc &= ~X;
        return Acc;
    });
}

unsigned BKDRHash(std::string_view Str) {
    return std::accumulate(Str.begin(), Str.end(), 
    0u, [](auto Acc, auto Sym) {
        static constexpr const unsigned Seed = 131;
        return (Acc * Seed) + Sym;
    });
}

unsigned SDBMHash(std::string_view Str) {
    return std::accumulate(Str.begin(), Str.end(), 
    0u, [](auto Acc, auto Sym) {
        return Sym + (Acc << 6) + (Acc << 16) - Acc;
    });
}

unsigned DJBHash(std::string_view Str) {
    return std::accumulate(Str.begin(), Str.end(), 
    5381u, [](auto Acc, auto Sym) {
        return ((Acc << 5) + Acc) + Sym;
    });
}

unsigned DEKHash(std::string_view Str) {
    return std::accumulate(Str.begin(), Str.end(), 
    static_cast<unsigned>(Str.size()), [](auto Acc, auto Sym) {
        return  ((Acc << 5) ^ (Acc >> 27)) ^ Sym;
    });
}

unsigned APHash(std::string_view Str) {
    unsigned I = 0;
    unsigned Hash = 0xAAAAAAAAu;
    for (auto Sym : Str) {
        Hash ^= ((I & 1) == 0) ? ((Hash <<  7) ^ Sym * (Hash >> 3)) :
                                (~((Hash << 11) + (Sym ^ (Hash >> 5))));
        ++I;
   }

   return Hash;
}

template<typename F>
unsigned long long countCollisions(const std::vector<std::string> &Vec, 
                                   F HashFun) {
    std::set<unsigned> Set;
    for (auto &&Str : Vec)
        Set.insert(std::invoke(HashFun, Str));  

    return Vec.size() - Set.size();
}
}

int main() {
    for (auto NumStrs = StrsNumInit; NumStrs < StrsNumFin; NumStrs += Step) {
        auto Vec = getNRandomStrings(NumStrs, /* seed */ 0u);
        std::cout << "NumStrs : " << NumStrs << "\n";
        std::cout << "\tRSHash : " << countCollisions(Vec, RSHash) << std::endl;
        std::cout << "\tJSHash : " << countCollisions(Vec, JSHash) << std::endl;
        std::cout << "\tPJWHash : " << countCollisions(Vec, PJWHash) << std::endl;
        std::cout << "\tELFHash : " << countCollisions(Vec, ELFHash) << std::endl;
        std::cout << "\tBKDRHash : " << countCollisions(Vec, BKDRHash) << std::endl;
        std::cout << "\tSDBMHash : " << countCollisions(Vec, SDBMHash) << std::endl;
        std::cout << "\tDJBHash : " << countCollisions(Vec, DJBHash) << std::endl;
        std::cout << "\tDEKHash : " << countCollisions(Vec, DEKHash) << std::endl;
        std::cout << "\tAPHash : " << countCollisions(Vec, APHash) << std::endl;
    }
}