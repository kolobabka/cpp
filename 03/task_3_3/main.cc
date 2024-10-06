#include <iostream>
#include "geom.h"

int main () {
    geom::Triangle Tr(3, 4, 5);
    std::cout << "Triangle: area = " << Tr.area()
              << ", perimeter = " << Tr.perimeter() << std::endl;
    geom::Rectangle Rect(2, 3);
    std::cout << "Rectangle: area = " << Rect.area()
              << ", perimeter = " << Rect.perimeter() << std::endl;

    geom::Square Square(5);
    std::cout << "Square: area = " << Square.area()
              << ", perimeter = " << Square.perimeter() << std::endl;

    geom::Ellipse Ells(5, 3);
    std::cout << "Ellipse: area = " << Ells.area()
              << ", perimeter = " << Ells.perimeter() << std::endl;

    geom::Circle Circ(2);
    std::cout << "Circle: area = " << Circ.area()
              << ", perimeter = " << Circ.perimeter() << std::endl;
}
