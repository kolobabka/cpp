#include <iostream>
#include <string>
#include <string_view>

struct Person final {
public:
    std::string Name;
    unsigned Age = 0;
    unsigned Height = 0;
};

class Builder {
private:
    Person P;
public:
    Builder& name(std::string_view Name) {
        P.Name = Name;
        return *this;
    }

    Builder& age(unsigned Age) & noexcept {
        P.Age = Age;
        return *this;
    }

    Builder& height(unsigned Height) & noexcept {
        P.Height = Height;
        return *this;
    }

    Person &get() & noexcept {
        return P;
    }
};

int main() {
    Builder B;
    Person P = B.name("Ivan").age(26).height(180).get();

    std::cout << "Name: " << P.Name << ", Age: " << P.Age << ", Height: " << P.Height << " cm" << std::endl;

    return 0;
}
