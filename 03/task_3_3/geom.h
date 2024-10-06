#ifndef _GEOM_H__
#define _GEOM_H__

#include <cmath>
#include <numbers>

namespace geom {
struct Shape {
    virtual double area() const = 0;
    virtual double perimeter() const = 0;

    virtual ~Shape() = default;
};

class Polygon : public Shape {
    unsigned NumSides;
public:
    Polygon(unsigned NumSides)
        : NumSides(NumSides) {}

    virtual ~Polygon () = default;
};

class Triangle final : public Polygon {
    double FirstSide, SecondSide, ThirdSide;
public:
    Triangle(double A, double B, double C)
        : Polygon(3),
          FirstSide(A), SecondSide(B), ThirdSide(C) {}

    double perimeter() const noexcept override {
        return FirstSide + SecondSide + ThirdSide;
    }

    double area() const noexcept override {
        auto Half = perimeter() / 2;
        return std::sqrt(Half * (Half - FirstSide) * (Half - SecondSide) * (Half - ThirdSide));
    }
};

class Rectangle : public Polygon {
    double Width, Height;
public:
    Rectangle (double Width, double Height)
        : Polygon (4),
          Width (Width), Height (Height) {}

    double perimeter() const noexcept override {
        return 2 * (Width + Height);
    }

    double area() const noexcept override {
        return Width * Height;
    }

    virtual ~Rectangle() = default;
};

struct Square final : public Rectangle {
    Square (double side)
        : Rectangle (side, side) {}
};

class Ellipse : public Shape {
    double MajorAxis, MinorAxis;
public:
    Ellipse(double MajorAxis, double MinorAxis)
        : MajorAxis (MajorAxis), MinorAxis (MinorAxis) {}

    double area() const noexcept override {
        return std::numbers::pi * MajorAxis * MinorAxis;
    }

    double perimeter() const noexcept override {
        return 4 * (area () + (MajorAxis - MinorAxis) * 
                   (MajorAxis - MinorAxis)) / (MajorAxis + MinorAxis);
    }

    virtual ~Ellipse () = default;
};

struct Circle final : public Ellipse {
    Circle (double R)
        : Ellipse (R, R) {}
};
} // namespace geom

#endif // _GEOM_H__
