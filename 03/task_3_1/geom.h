#ifndef _GEOM_H__
#define _GEOM_H__

namespace geom {
struct Rectangle final {
    int X = 0, Y = 0;
    int Width = 0, Height = 0;
    Rectangle() = default;
    Rectangle (int X, int Y, int Width, int Height)
        : X(X), Y(Y), Width(Width), Height(Height) {}

    int getTopCoord () const noexcept { return Y + Height; }

    int getRightCoord () const noexcept { return X + Width; }

    int getLeftCoord () const noexcept { return X; }

    int getBottomCoord () const noexcept { return Y; }
};
} // namespace geom

#endif // _GEOM_H__
