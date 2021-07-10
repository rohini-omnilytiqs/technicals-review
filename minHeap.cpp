// a min heap is a complete binary tree where every node is smaller than its children
// this the minimum is the root node 
// typically implemented as an array 
// provides O(log n) operations
#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
    private:
        vector<int> heap; // stores heap in array representation
        void heapifyDown(); // O(log n)
        void heapifyUp(); // O(log n)
        int getRightChildIdx(int idx); // O(1)
        int getLeftChildIdx(int idx); // O(1)
        int getParentIdx(int idx); // O(1)

    public:
        MinHeap(){};
        int top(); // O(1)
        void push(int value); // O(log n)
        void pop(); // O(log n)
        void print(); // O(log n)
};

int MinHeap::getRightChildIdx(int idx){
    return idx*2+2;
}

int MinHeap::getLeftChildIdx(int idx){
    return idx*2+1;
}

int MinHeap::getParentIdx(int idx){
    if (idx % 2 == 0){
        return (idx-2)/2;
    }
    else {
        return (idx-1)/2;
    }
}

// reconstructs heap when new node is added as leaf 
// continues swapping the leaf node up until its parent is smaller than it
// probably should be implemented recursively
void MinHeap::heapifyUp(){
    if (heap.size() == 1) return;
    bool ordered = false;
    int childIdx = heap.size()-1;
    while (!ordered){
        int parentIdx = getParentIdx(childIdx);
        if (heap[childIdx] > heap[parentIdx]){
            ordered = true;
        }
        else {
            swap(heap[childIdx], heap[parentIdx]);
            childIdx = parentIdx;
        }
    }
}

// reconstructs heap when root is removed and replaced with leaf
// continues swapping the root with its smallest child until children are larger than it
// also probably should be implemented recursively
void MinHeap::heapifyDown(){
    bool ordered = false;
    int parentIdx = 0;

    while (!ordered) { 
        int leftChildIdx = getLeftChildIdx(parentIdx);
        int rightChildIdx = getRightChildIdx(parentIdx);

        if ((leftChildIdx > heap.size()-1) || (rightChildIdx > heap.size()-1)) return;
        if (heap[parentIdx] < heap[leftChildIdx]){
            if (heap[parentIdx] < heap[rightChildIdx]) {
                ordered = true;
            }
            else {
                swap(heap[parentIdx], heap[rightChildIdx]);
                parentIdx = rightChildIdx;
            }
        }
        else { 
            if (heap[rightChildIdx]<heap[leftChildIdx]){
                swap(heap[parentIdx], heap[rightChildIdx]);
                parentIdx = rightChildIdx;
            }
            else {
                swap(heap[parentIdx], heap[leftChildIdx]);
                parentIdx = leftChildIdx;
            }
        }
    }

}

// returns minimum in heap
int MinHeap::top(){
    return heap[0];
}

// inserts into heap by adding a leaf and fixing the heap
void MinHeap::push(int value){
    heap.push_back(value);
    heapifyUp();
}

// removes minimum from heap by swapping heap with the last element and fixing the heap
void MinHeap::pop(){
    if (heap.size() == 0) return;
    heap[0] = heap[heap.size()-1];
    heap.pop_back();
    heapifyDown();
}

// helper for testing
void MinHeap::print(){
    vector<int>::iterator it; 
    for (it=heap.begin(); it != heap.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    MinHeap myHeap = MinHeap();
    myHeap.push(1);
    myHeap.push(10);
    myHeap.push(8);
    myHeap.push(6);
    myHeap.push(9);
    myHeap.push(11);
    myHeap.push(5);
    myHeap.print();

    cout << "Minimum is " << myHeap.top() << endl;
    myHeap.pop();
    myHeap.print();
    return 0;
}