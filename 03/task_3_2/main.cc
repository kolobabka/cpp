#include <iostream>
#include "geom.h"

int main () {
    geom::Triangle Tr(geom::Point(0, 0), geom::Point(1, 1), geom::Point(-1, 1));
    std::cout << "Triangle: area = " << Tr.area() << ", perimeter = " << Tr.perimeter() << std::endl;

    geom::Square Sq (geom::Point (2, 2), 3);
    std::cout << "Square: area = " << Sq.area() << ", perimeter = " << Sq.perimeter() << std::endl;

    geom::Circle Cir (geom::Point (0, 0), 1);
    std::cout << "Circle: area = " << Cir.area() << ", perimeter = " << Cir.perimeter() << std::endl;
}
