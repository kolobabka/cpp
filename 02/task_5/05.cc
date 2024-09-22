#include <iostream>
#include <numbers>
#include <cmath>
#include <iomanip>


double eCalc () {
    static constexpr const double Epsilon = 10E-15;
    double Res = 0.0;
    double Term = 1.0;

    for (unsigned Denom = 1; Term > Epsilon; ++Denom) {
        Res += Term;
        Term /= Denom;
    }

    return Res;
}

int main ()
{
    double E = eCalc ();

    std::cout << std::setprecision (17);
    std::cout << "My e : " << E << std::endl;
    std::cout << "std::numbers::e : " << std::numbers::e << std::endl;
    std::cout << "Diff : " << std::fabs (E - std::numbers::e) << std::endl;
}

