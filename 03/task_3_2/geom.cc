#include "geom.h"

double geom::crossProdAbs(const geom::Vec &Vec1, const geom::Vec &Vec2) {
    auto X1 = Vec1.getX();
    auto Y1 = Vec1.getY();

    auto X2 = Vec2.getX();
    auto Y2 = Vec2.getY();

    return std::abs(X1 * Y2 - X2 * Y1);
}
