#include <iostream>
#include <vector>
#include <cmath>

struct BinomialNode {
    int Key;
    int Degree;
    BinomialNode* Parent;
    BinomialNode* Child;
    BinomialNode* Sibling;

    BinomialNode(int K) : Key(K), Degree(0), Parent(nullptr), Child(nullptr), Sibling(nullptr) {}
};

class BinomialHeap {
private:
    std::vector<BinomialNode*> Roots;

    void linkTrees(BinomialNode* Y, BinomialNode* Z) {
        Y->Parent = Z;
        Y->Sibling = Z->Child;
        Z->Child = Y;
        Z->Degree++;
    }

public:
    void insert(int Key) {
        BinomialNode* Node = new BinomialNode(Key);
        Roots.push_back(Node);
    }
};

int main() {
    BinomialHeap BH;
    BH.insert(10);
    BH.insert(20);
    return 0;
}