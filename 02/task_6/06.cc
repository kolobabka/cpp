#include <iostream>
#include <unordered_map>

unsigned evaluateCollatzSeqLength (unsigned Num, std::unordered_map<unsigned, unsigned>& Cache) {
    unsigned ResNum = Num;
    unsigned Len = 1;

    while (Num != 1) {
        if (Cache.find (Num) != Cache.end()) {
            Len += Cache [Num] - 1;
            break;
        }

        if (Num % 2 == 0)
            Num >>= 1;
        else
            Num = 3 * Num + 1;

        Len++;
    }

    Cache[ResNum] = Len;
    return Len;
}

void evaluateLongestCollatzSeq(unsigned Limit) {
    std::unordered_map<unsigned, unsigned> Cache;
    unsigned MaxLenght = 0;
    unsigned NumForMaxSeq = 0;

    for (unsigned Num = 1; Num <= Limit; ++Num) {
        unsigned Length = evaluateCollatzSeqLength(Num, Cache);
        if (Length > MaxLenght) {
            MaxLenght = Length;
            NumForMaxSeq = Num;
        }
    }

    std::cout << "Number that gives the longest Collatz sequence : " << NumForMaxSeq << std::endl;
    std::cout << "Collatz sequence length : " << MaxLenght << std::endl;
}

int main ()
{
    unsigned Limit;
    std::cin >> Limit;
    evaluateLongestCollatzSeq(Limit);
}

