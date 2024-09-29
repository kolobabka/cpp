#include <iostream>
#include <istream>
#include <vector>
#include <algorithm>
#include "geom.h"

namespace {
int evalIntersectArea (const geom::Rectangle &First, const geom::Rectangle &Second)
{
    auto Left = std::max(First.getLeftCoord(), Second.getLeftCoord());
    auto Top = std::min(First.getTopCoord(), Second.getTopCoord());
    auto Right = std::min(First.getRightCoord(), Second.getRightCoord());
    auto Bottom = std::max(First.getBottomCoord(), Second.getBottomCoord());

    auto Width = Right - Left;
    auto Height = Top - Bottom;

    if (Width < 0 || Height < 0)
        return 0;

    return Width * Height;
}

void intersectArea(const std::vector<geom::Rectangle>& Rects) {
    if (Rects.empty ())
        return;

    for (auto FirstIdx = 0; FirstIdx < Rects.size (); ++FirstIdx) {
        for (auto SecondIdx = FirstIdx; SecondIdx < Rects.size(); ++SecondIdx) {
            auto Area = evalIntersectArea (Rects[FirstIdx], Rects[SecondIdx]);
            std::cout << "Intersection area of rectangle #" << FirstIdx
                      << " and rectangle #" << SecondIdx
                      << " is " << Area << std::endl;
        }
    }
}

std::istream &operator>>(std::istream &In, geom::Rectangle &Rectangle) {
    In.exceptions(std::istream::failbit);
    In >> Rectangle.X >> Rectangle.Y >> Rectangle.Width >> Rectangle.Height;

    return In; 
}

std::vector<geom::Rectangle> getRectanglesFromInput(unsigned N) {
    std::vector<geom::Rectangle> Rectangles;
    Rectangles.reserve(N);
    for (auto Idx = 0u; Idx < N; ++Idx) {
        geom::Rectangle Rect;
        std::cin >> Rect;
        Rectangles.push_back(std::move(Rect));
    }

    return Rectangles;
}
}

int main () {
    std::vector<geom::Rectangle> Rectangles;
    unsigned N; 
    std::cin >> N;
    if (!std::cin) {
        std::cerr << "Wrong input for number of rectangles!" << std::endl;
        return -1;
    }
    try {
        Rectangles = getRectanglesFromInput(N);
    } catch(std::ios_base::failure &fail) {
        std::cerr << fail.what() << ": can not read rectangles" << std::endl;
        return -1;
    }
    intersectArea(Rectangles);
}

