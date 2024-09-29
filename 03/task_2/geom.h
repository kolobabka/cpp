#ifndef _GEOM_H__
#define _GEOM_H__

#include <cmath>
#include <utility>

namespace geom {
struct Figure {
    virtual double area () const = 0;
    virtual double perimeter () const = 0;
    virtual ~Figure () {}
};

struct Point {
    double X;
    double Y;

    Point (double X, double Y)
        : X(X), Y(Y) {}

    double getX() const noexcept { return X; }

    double getY() const noexcept { return Y; }
};

class Vec final {
    Point P1;
    Point P2;
public:
    Vec (const Point &P1, const Point &P2)
        : P1(P1), P2(P2) {}

    Vec (Point &&P1, Point &&P2)
        : P1(std::move(P1)), P2(std::move(P2)) {}

    double length() const {
        auto XDiff = getX();
        auto YDiff = getY();
        return std::sqrt(XDiff * XDiff + YDiff * YDiff);
    }

    double getX() const noexcept { return P2.getX () - P1.getX (); }
    double getY() const noexcept { return P2.getY () - P1.getY (); }

    Point getP1() const noexcept { return P1; }
    Point getP2() const noexcept { return P2; }
};

double crossProdAbs (const Vec &Vec1, const Vec &Vec2);

class Triangle final : public Figure {
    Vec Side1, Side2;
public:
    Triangle (const Point &P1, const Point &P2, const Point &P3)
        : Side1 (P1, P2), Side2 (P1, P3) {}

    double area() const noexcept {
        return crossProdAbs (Side1, Side2) / 2;
    }

    double perimeter() const noexcept {
        Vec Size3 (Side1.getP2(), Side2.getP2());
        return Side1.length() + Side2.length() + Size3.length();
    }

    Vec getSide1() const noexcept {
        return Side1;
    }

    Vec getSide2() const noexcept {
        return Side2;
    }
};

class Square final : public Figure {
    Vec Side1, Side2;
public:
    Square (const Point &p1, double signed_len)
        : Side1 (p1, Point (p1.getX () + signed_len, p1.getY ())),
          Side2 (p1, Point (p1.getX (), p1.getY () + signed_len)) {}

    double area() const noexcept {
        return crossProdAbs(Side1, Side2);
    }

    double perimeter() const noexcept {
        return 4 * Side1.length();
    }

    Vec getSide1() const noexcept {
        return Side1;
    }

    Vec getSide2() const noexcept {
        return Side2;
    }
};

class Circle final : public Figure {
    Point Center;
    double Radius;
public:
    static constexpr double Pi = 3.1415;

    Circle (const Point &Center, double Radius)
        : Center (Center), Radius (Radius) {}

    double area() const noexcept {
        return Pi * Radius * Radius;
    }

    double perimeter() const noexcept {
        return 2 * Pi * Radius;
    }

    Point getCenter() const noexcept {
        return Center;
    }

    double getRadius() const noexcept {
        return Radius;
    }
};

} // namespace geom

#endif // _GEOM_H__
