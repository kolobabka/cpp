#include <iostream>

struct Base1 {
    virtual void foo() {
        std::cout << "Foo in Base1" << std::endl;
    }
    virtual ~Base1() = default;
};

struct Base2 {
    virtual void foo() {
        std::cout << "Foo in Base2" << std::endl;
    }
    virtual ~Base2() = default;
};

struct DummyBase1 : public Base1 {
    virtual void Base1Foo() = 0;
private:
    void foo() {
        Base1Foo();
    }
public:
    virtual ~DummyBase1() = default;
};

struct DummyBase2 : public Base2 {
    virtual void Base2Foo() = 0;
private:
    void foo() {
        Base2Foo();
    }
public:
    virtual ~DummyBase2() = default;
};

struct Derived final : public Base1, public Base2 {
    void foo() override {
        std::cout << "Foo in Derived" << std::endl;
    }
};

struct DerivedCorrect final : public DummyBase1, public DummyBase2 {
    void Base1Foo() override {
        std::cout << "Base1Foo in Derived" << std::endl;
    }

    void Base2Foo() override {
        std::cout << "Base2Foo in Derived" << std::endl;
    }
};


int main () {
    Derived Der;
    Base1 *B1 = &Der;
    Base2 *B2 = &Der;

    std::cout << "Calling foo from Derived instance" << std::endl; 
    Der.foo();
    std::cout << "-------------" << std::endl;

    std::cout << "Calling foo from Base1 pointer" << std::endl; 
    B1->foo();
    std::cout << "-------------" << std::endl;

    std::cout << "Calling foo from Base2 pointer" << std::endl; 
    B2->foo();
    std::cout << "-------------" << std::endl;

    std::cout << "\tAs we can see, there are only calling foo from dervied" << std::endl;

    std::cout << "\tTo solve this problem we need to create two dummy classes" << std::endl;
    std::cout << "-------------" << std::endl;
    DerivedCorrect DerCorr;
    Base1 *BCorr1 = &DerCorr;
    Base2 *BCorr2 = &DerCorr;

    std::cout << "Calling foo from Base1 pointer" << std::endl; 
    BCorr1->foo();
    std::cout << "-------------" << std::endl;
    std::cout << "Calling foo from Base2 pointer" << std::endl; 
    BCorr2->foo();
    std::cout << "-------------" << std::endl;
    std::cout << "\tAs a result we have two different override functions for different foo from the base classes" << std::endl;
}
