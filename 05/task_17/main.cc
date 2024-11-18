#include <iostream>
#include <string>
#include <string_view>

template <typename Implementation>
class DrawingImplementation {
public:
    void drawLine(std::string_view Start, std::string_view End) const {
        static_cast<const Implementation*>(this)->drawLineImpl(Start, End);
    }

    void drawCircle(std::string_view center, double Radius) const {
        static_cast<const Implementation*>(this)->drawCircleImpl(center, Radius);
    }
};

class PixelDrawing : public DrawingImplementation<PixelDrawing> {
public:
    void drawLineImpl(std::string_view Start, std::string_view End) const {
        std::cout << "Drawing pixel line from " << Start << " to " << End << std::endl;
    }

    void drawCircleImpl(std::string_view Center, double Radius) const {
        std::cout << "Drawing pixel circle at " << Center << " with radius " << Radius << std::endl;
    }
};

class VectorDrawing : public DrawingImplementation<VectorDrawing> {
public:
    void drawLineImpl(std::string_view Start, std::string_view End) const {
        std::cout << "Drawing vector line from " << Start << " to " << End << std::endl;
    }

    void drawCircleImpl(std::string_view Center, double Radius) const {
        std::cout << "Drawing vector circle at " << Center << " with radius " << Radius << std::endl;
    }
};

// Абстракция "Форма"
template <typename DrawingImpl>
class Shape {
protected:
    const DrawingImpl &drawingImpl;

public:
    Shape(const DrawingImpl& Impl) : drawingImpl(Impl) {}

    virtual ~Shape() = default;

    virtual void draw() = 0; // Абстрактный метод для рисования
};

// Конкретная форма: Линия
template <typename DrawingImpl>
class Line final : public Shape<DrawingImpl> {
    std::string Start, End;

public:
    Line(const DrawingImpl& Impl, std::string_view Start, std::string_view End)
        : Shape<DrawingImpl>(Impl), Start(Start), End(End) {}

    void draw() override {
        this->drawingImpl.drawLine(Start, End);
    }
};

// Конкретная форма: Круг
template <typename DrawingImpl>
class Circle final : public Shape<DrawingImpl> {
    std::string Center;
    double Radius;

public:
    Circle(const DrawingImpl& impl, std::string_view Center, double Radius)
        : Shape<DrawingImpl>(impl), Center(Center), Radius(Radius) {}

    void draw() override {
        this->drawingImpl.drawCircle(Center, Radius);
    }
};

int main() {
    // Используем пиксельную графику для рисования
    PixelDrawing PDrawing;
    Line<PixelDrawing> PLine(PDrawing, "A", "B");
    Circle<PixelDrawing> PCircle(PDrawing, "Center", 5.0);

    std::cout << "Using PixelDrawing:" << std::endl;
    PLine.draw();
    PCircle.draw();

    // Используем векторную графику для рисования
    VectorDrawing VDrawing;
    Line<VectorDrawing> VLine(VDrawing, "X", "Y");
    Circle<VectorDrawing> VCircle(VDrawing, "Origin", 10.0);

    std::cout << std::endl;

    std::cout << "Using VectorDrawing:" << std::endl;
    VLine.draw();
    VCircle.draw();

    return 0;
}
