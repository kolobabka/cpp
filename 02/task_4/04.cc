#include <iostream>
#include <numeric>

int gcdRecursive (int X, int Y) {
    if (Y == 0)
        return X;

    return gcdRecursive (Y, X % Y);
}

int gcdIterative (int X, int Y) {
    while (Y != 0)
    {
        int tmp = Y;
        Y = X % Y;
        X = tmp;
    }

    return X;
}

int lcm (int X, int Y) {
    return X * (Y / gcdIterative(X, Y));
}

int main ()
{
    int N = 0;
    std::cin >> N;
    for (int X = 1; X < N; ++X)
        for (int Y = 1; Y < N; ++Y) {
            int GCDRecursive = gcdRecursive(X, Y);
            int GCDIterative = gcdIterative(X, Y);
            int LCM = lcm(X, Y);

            if (GCDRecursive != std::gcd(X, Y))
                std::cerr << "Recursive gcd mismatch" << std::endl;
            else
                std::cout << "Recursive gcd is the same to standard!" << std::endl;

            if (GCDIterative != std::gcd(X, Y))
                std::cerr << "Iterative gcd mismatch" << std::endl;
            else
                std::cout << "Iterative gcd is the same to standard!" << std::endl;

            if (LCM != std::lcm(X, Y)) 
                std::cerr << "LCM mismatch" << std::endl;
        }
}

