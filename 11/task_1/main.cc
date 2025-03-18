struct Proxy;
Proxy f();

struct Proxy {
    Proxy operator()() {
      return f();
    }
};

Proxy f() {  
    return Proxy();
}

int main() {
    f()()()()();
}

