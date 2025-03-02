# Кучи

1. Куча для максимума (max-heap) — это структура данных, в которой ключ родительского узла не меньше ключей его потомков.  
   * На вершине кучи (корне) находится максимальный элемент.  
   * Используется для реализации очередей с приоритетами. 

2. Двоичная куча (Binary Heap) — это полное бинарное дерево, удовлетворяющее свойству кучи (родитель ≥ потомков в max-heap).  
   * Эффективна для операций вставки $O(log (n))$ и извлечения максимума $O(log (n))$.  
   * Часто реализуется на массиве.  

```c++
class MaxHeap {
    std::vector<int> Heap;

    void heapifyDown(int I) {
        int Left = 2 * I + 1;
        int Right = 2 * I + 2;
        int Largest = I;

        if (Left < Heap.size() && Heap[Left] > Heap[Largest]) 
            Largest = Left;
        if (Right < Heap.size() && Heap[Right] > Heap[Largest]) 
            Largest = Right;

        if (Largest != I) {
            std::swap(Heap[I], Heap[Largest]);
            heapifyDown(Largest);
        }
    }

    void heapifyUp(int I) {
        int Parent = (I - 1) / 2;
        if (I > 0 && Heap[I] > Heap[Parent]) {
            std::swap(Heap[I], Heap[Parent]);
            heapifyUp(Parent);
        }
    }

public:
    void insert(int Val) {
        Heap.push_back(Val);
        heapifyUp(Heap.size() - 1);
    }

    int extractMax() {
        if (Heap.empty()) return -1;
        int MaxVal = Heap[0];
        Heap[0] = Heap.back();
        Heap.pop_back();
        heapifyDown(0);
        return MaxVal;
    }
};

```

3. Биномиальная куча (Binomial Heap) — это набор биномиальных деревьев, объединенных по свойству кучи.  
   * Поддерживает эффективное объединение $O(log (n))$.  
   * Используется в алгоритмах Дейкстры и Прима.  

```c++

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

```

4. Фибоначчиева куча (Fibonacci Heap) — это набор слабоупорядоченных деревьев, где минимальный элемент поддерживается явно.  
   * Улучшает амортизированное время некоторых операций (например, decrease-key за $O(1)$).  
   * Применяется в алгоритмах на графах (Дейкстра, Прим).  

```c++

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

```