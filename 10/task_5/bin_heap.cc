#include <iostream>
#include <vector>

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
        if (Heap.empty()) 
            return -1;
        int MaxVal = Heap[0];
        Heap[0] = Heap.back();
        Heap.pop_back();
        heapifyDown(0);
        return MaxVal;
    }
};

int main() {
    MaxHeap H;
    H.insert(10);
    H.insert(20);
    H.insert(15);
    std::cout << H.extractMax() << std::endl; // 20
}