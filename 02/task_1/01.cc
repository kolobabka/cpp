#include <iostream>
#include <iterator>
#include <cctype>
#include <cassert>
#include <string>

enum SymbT
{
    DECIMAL,   // Decimal number {0, ..., 9}
    OPERATION, // Arithmetical operattor {+, -, *, /}
    BRACKET,   // Round brackets {(, )}
    OTHERS,    // All others. (including trailing white spaces) 
};

std::ostream &operator<<(std::ostream &Os, SymbT Type) {
  using enum SymbT;
  const char *Str = "Unknown";
  switch (Type) {
#ifdef SYMBOL_CASE
#error "expected SYMBOL_CASE macro to be undefined"
#endif
#define SYMBOL_CASE(X)                                                         \
  case X:                                                                      \
    Str = #X;                                                                  \
    break;
    SYMBOL_CASE(DECIMAL)
    SYMBOL_CASE(OPERATION)
    SYMBOL_CASE(BRACKET)
    SYMBOL_CASE(OTHERS)
#undef SYMBOL_CASE
  default:
    assert(0 && "Unhandled AccessType value");
  }
  Os << Str;
  return Os;
}

SymbT getSymbT (auto Symb)
{
    if (std::isdigit (Symb))
        return DECIMAL;

    switch (Symb)
    {
        case '+':
        case '-':
        case '*':
        case '/':
            return OPERATION;
        case '(':
        case ')':
            return BRACKET;
        default:
            return OTHERS;
    }
}

int main ()
{
    std::istreambuf_iterator<char> Begin(std::cin), End;
    std::string Buf(Begin, End);

    for (auto &&Symb : Buf)
        std::cout << getSymbT(Symb) << std::endl;
}

