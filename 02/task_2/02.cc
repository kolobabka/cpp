#include <iostream>
#include <cmath>
#include <unordered_set>
#include <utility>

template <typename T>
T nthPower(T X, T Acc, unsigned N) {  
    while (N > 0) {
        if ((N & 0x1) == 0x1) {
            Acc *= X;
            N -= 1;
        }
        X *= X;
        N /= 2;
    }
    return Acc;
}

unsigned nthPower(unsigned X, unsigned N) {
    if (X < 2u || N == 1u)
        return X;
    return nthPower<unsigned>(X, 1u, N);
}

bool isArmstrong(unsigned N)
{
    unsigned Tmp = N;
    unsigned Sum = 0;
    unsigned NumDigets = std::log10(N) + 1;

    while (N > 0) {
        unsigned CurDigit = N % 10;
        Sum += nthPower(CurDigit, NumDigets);
        N /= 10;
    }

    return Sum == Tmp;
}

void armstrong(unsigned N)
{
    for (unsigned CurNum = 1, Idx = 0; CurNum < N; ++CurNum)
        if (isArmstrong (CurNum))
            std::cout << "Armstrong #" << Idx++ << " " << CurNum << std::endl;
}

void fib(int N)
{
    unsigned Cur = 1, Prev = 0, Idx = 0;

    for (Idx; Prev < N; ++Idx) {
        std::cout << "Fib #" << Idx  + 1 << " " << Prev << std::endl;
        Prev = std::exchange(Cur, Cur + Prev);
    }
}

unsigned checkSumProperDivision(unsigned Num)
{
    unsigned Sum = 1;
    unsigned Sqrt = std::sqrt(Num);

    for (int Idx = 2; Idx <= Sqrt; ++Idx) {
        if (Num % Idx == 0) {
            Sum += Idx;
            if (Idx != Num / Idx) {
                Sum += Num / Idx;
            }
        }
    }
    return Sum;
}

void abundant(unsigned N)
{
    constexpr const auto Min = 12;
    for (unsigned CurNum = 1, Idx = 0; CurNum < N; ++CurNum)
        if (checkSumProperDivision(CurNum) > CurNum)
            std::cout << "Abundant #" << Idx++ << " " << CurNum << std::endl;
}

void amicable(unsigned N)
{
    std::unordered_set<unsigned> HereYet;

    for (int CurNum = 2, Idx = 0; CurNum < N; ++CurNum) {
        if (HereYet.find(CurNum) != HereYet.end())
            continue;

        auto Sum = checkSumProperDivision(CurNum);
        if (Sum != CurNum && checkSumProperDivision(Sum) == CurNum)
        {
            std::cout << "Amicable #" << Idx++ << " (" << CurNum << ", " << Sum << ")" << std::endl;
            HereYet.insert(CurNum);
            HereYet.insert(Sum);
        }
    }
}

int main ()
{
    unsigned N = 0;
    std::cin >> N;

    std::cout << "------------------------" << std::endl;
    armstrong(N);

    std::cout << "------------------------" << std::endl;
    fib(N);

    std::cout << "------------------------" << std::endl;
    abundant(N);

    std::cout << "------------------------" << std::endl;
    amicable(N);
}

