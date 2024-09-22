#include <iostream>

void is_prime(unsigned N) {
  if (N <= 1)
    return;
  if ((N == 2) || (N == 3)) {
    std::cout << N << std::endl;
    return;
  }
  if (((N % 2) == 0))
    std::cout << "2" << std::endl;

  if ((N % 3) == 0)
    std::cout << "3" << std::endl;

  unsigned J = 5;
  bool IsPrime = true;
  for (; J < N; J += 6) {
    if ((N % J) == 0) {
        std::cout << J << std::endl;
        IsPrime = false;
    }
    else if ((N % (J + 2)) == 0) {
        std::cout << J + 2 << std::endl;
        IsPrime = false;
    }
  }
  if (IsPrime)
    std::cout << N << std::endl;
}

int main ()
{
    unsigned N = 0;
    std::cin >> N;
    is_prime(N);
}

