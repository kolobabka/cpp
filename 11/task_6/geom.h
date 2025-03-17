#ifndef _GEOM_H__
#define _GEOM_H__

#include <sstream>
#include <cmath>

namespace my_geom {

struct Visitor {
    virtual void visit(const class Triangle& triangle) = 0;
    virtual void visit(const class Square& square) = 0;
    virtual void visit(const class Circle& circle) = 0;
};

struct Figure {
    virtual double area () const = 0;
    virtual double perimeter () const = 0;
    virtual ~Figure () {}

    /* Double dispatching.  */
    virtual void accept(class Visitor& visitor) const = 0;
};

class Point {
    double x;
    double y;

public:
    Point (double x_, double y_)
        : x (x_), y (y_) {}

    double get_x () const
    {
        return x;
    }

    double get_y () const
    {
        return y;
    }
};

class Vec final {
    Point p1;
    Point p2;

public:
    Vec (const Point &p1_, const Point &p2_)
        : p1 (p1_), p2 (p2_) {}

    double length () const
    {
        double x_diff = get_x ();
        double y_diff = get_y ();
        return std::sqrt (x_diff * x_diff + y_diff * y_diff);
    }

    double get_x () const { return p2.get_x () - p1.get_x (); }
    double get_y () const { return p2.get_y () - p1.get_y (); }

    Point get_p1 () const { return p1; }
    Point get_p2 () const { return p2; }
};

double cross_prod_module (const Vec &vec1, const Vec &vec2) {
    double x1 = vec1.get_x ();
    double y1 = vec1.get_y ();

    double x2 = vec2.get_x ();
    double y2 = vec2.get_y ();

    return std::abs (x1 * y2 - x2 * y1);
}

class Triangle final : public Figure {
    Vec side1, side2;

public:
    Triangle (const Point &p1_, const Point &p2_, const Point &p3_)
        : side1 (p1_, p2_), side2 (p1_, p3_) {}

    double area () const
    {
        return cross_prod_module (side1, side2) / 2;
    }

    double perimeter () const
    {
        Vec side3_ (side1.get_p2 (), side2.get_p2 ());
        return side1.length () + side2.length () + side3_.length ();
    }

    Vec get_side1 () const
    {
        return side1;
    }

    Vec get_side2 () const
    {
        return side2;
    }

    void accept(Visitor& visitor) const override
    {
        visitor.visit (*this);
    }
};

class Square final : public Figure {
    Vec side1, side2;

public:
    Square (const Point &p1, double signed_len)
        : side1 (p1, Point (p1.get_x () + signed_len, p1.get_y ())),
          side2 (p1, Point (p1.get_x (), p1.get_y () + signed_len)) {}

    double area () const
    {
        return cross_prod_module (side1, side2);
    }

    double perimeter () const
    {
        return 4 * side1.length ();
    }

    Vec get_side1 () const
    {
        return side1;
    }

    Vec get_side2 () const
    {
        return side2;
    }

    void accept(Visitor& visitor) const override
    {
        visitor.visit (*this);
    }
};

class Circle final : public Figure {
    Point center;
    double radius;

public:
    static constexpr double Pi = 3.1415;

    Circle (const Point &center_, double radius_)
        : center (center_), radius (radius_) {}

    double area () const
    {
        return Pi * radius * radius;
    }

    double perimeter () const
    {
        return 2 * Pi * radius;
    }

    Point get_center () const
    {
        return center;
    }

    double get_radius () const
    {
        return radius;
    }

    void accept(Visitor& visitor) const override
    {
        visitor.visit (*this);
    }
};

class StringVisitor : public Visitor {
    std::ostringstream oss;

public:
    void visit(const Triangle& triangle) override
    {
        oss << "Triangle: Area = " << triangle.area () << ", Perimeter = " << triangle.perimeter () << "\n";
    }

    void visit(const Square& square) override
    {
        oss << "Square: Area = " << square.area () << ", Perimeter = " << square.perimeter () << "\n";
    }

    void visit(const Circle& circle) override
    {
        oss << "Circle: Area = " << circle.area () << ", Perimeter = " << circle.perimeter () << "\n";
    }

    std::string get_result() const
    {
        return oss.str();
    }
};

} // namespace my_geom

#endif

