#include <iostream>
#include <vector>

struct FibNode {
    int Key;
    FibNode* Parent;
    FibNode* Child;
    FibNode* Next;
    bool Marked;
    int Degree;

    FibNode(int K) : Key(K), Parent(nullptr), Child(nullptr), Next(this), Marked(false), Degree(0) {}
};

class FibonacciHeap {
    FibNode* MinNode = nullptr;

public:
    void insert(int Key) {
        FibNode* Node = new FibNode(Key);
        if (!MinNode) {
            MinNode = Node;
        } else {
            Node->Next = MinNode->Next;
            MinNode->Next = Node;
            if (Node->Key < MinNode->Key)
                MinNode = Node;
        }
    }

    int getMin() {
        return MinNode ? MinNode->Key : -1;
    }
};

int main() {
    FibonacciHeap FH;
    FH.insert(10);
    FH.insert(5);
    FH.insert(20);
    std::cout << FH.getMin() << std::endl; // 5
}