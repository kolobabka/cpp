#include <iostream>

/* Let's abuse for compiler's extension.  */
__attribute__((constructor)) static void HelloGnu () {
    std::cout << "1) Hello from GNU extensions" << std::endl;
}

/* Global object initialization happens before main().  */
struct Printer final {
    Printer() { std::cout << "2) Hello from constructor of global object!" << std::endl; }
    ~Printer() { std::cout << "3) Destructor will do the same." << std::endl; }
};
Printer Print;

/* Kinda same hack as above.  */
static int AnotherGlobalPrint () {
    std::cout << "4) Another hack with global objects!" << std::endl;
    return 0;
}
int Global_Print = AnotherGlobalPrint ();

void init_section_fun () {
    std::cout << "5) It's gone too far... Hi from .init_array section" << std::endl;
}

/* All functions that happens BEFORE main() exists in .init_array section.  */
__attribute__((section(".init_array"))) void (*p_init)(void) = &init_section_fun;

void fini_section_fun () {
    std::cout << "6) Hi from .fini_array section" << std::endl;
}

/* All functions that happens AFTER main() exists in .fini_array section.  */
__attribute__((section(".fini_array"))) void (*p_fini)(void) = &fini_section_fun;

int main() {

}

