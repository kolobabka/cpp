#include <iostream>
#include <vector>
#include <deque>

template<typename T>
struct Stack : private std::deque<T> {
private:
    using std::deque<T>::front;
    using std::deque<T>::pop_front;
    using std::deque<T>::push_front;
    using std::deque<T>::emplace_front;
public:
    using std::deque<T>::empty;
    using std::deque<T>::size;
    using std::deque<T>::swap;
    using container_type = typename std::deque<T>;
    using typename std::deque<T>::value_type;
    using typename std::deque<T>::size_type;
    using typename std::deque<T>::reference;
    using typename std::deque<T>::const_reference;

    Stack() {}
    explicit Stack(const container_type& Cont) : container_type(Cont) {}
    explicit Stack(container_type&& Cont) : container_type(std::move(Cont)) {}

    void push(const value_type& Value) {
        push_front(Value);
    }

    void push(value_type&& Value) {
        push_front(std::move(Value));
    }

    template< class... Args >
    decltype(auto) emplace( Args&&... args ) {
        return emplace_front(args...);
    }

    void pop() {
        pop_front();
    }

    reference top() {
        return front();
    }

    const_reference top() const {
        return front();
    }
};

int main() {
    std::deque Deq = {5, 4, 3, 2, 1};
    Stack<int> St(Deq);
    
    std::cout << "Init state: Stack = {5, 4, 3, 2, 1}" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    
    int NewVal = 6;
    std::cout << "Push " << NewVal << std::endl;
    St.push(NewVal);
    
    std::cout << "---------------------------------------" << std::endl;
    NewVal = 7;
    std::cout << "Emplace " << NewVal << std::endl;
    St.emplace(NewVal);

    std::cout << "---------------------------------------" << std::endl;
    while (!St.empty()) {
        std::cout << "St.top : " << St.top() << std::endl;
        std::cout << "St.pop" << std::endl;
        St.pop();
        std::cout << "---------------------------------------" << std::endl;
    }

    return 0;
}
