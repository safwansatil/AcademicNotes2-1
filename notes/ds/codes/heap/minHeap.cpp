#include <bits/stdc++.h>
using namespace std;

class MinHeap
{
private:
    vector<int> heap;

    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void bubbleUp(int i)
    {
        while (i > 0 && heap[parent(i)] > heap[i])
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void bubbleDown(int i)
    {
        int smallest = i;
        int n = heap.size();
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < n && heap[left] < heap[smallest])
        {
            smallest = left;
        }
        if (right < n && heap[right] < heap[smallest])
        {
            smallest = right;
        }
        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            bubbleDown(smallest);
        }
    }

public:
    void push(int value){
        heap.push_back(value);
        bubbleUp(heap.size()-1); // 0-based indexing

    }
    int pop(){
        if(heap.empty()){
            return -1;
        }
        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if(!heap.empty()){
            bubbleDown(0);
        }
        return root;
    }
    int top(){
        if(heap.empty()){
            return -1;
        }
        return heap[0];
    }
    bool empty(){
        return heap.empty();
    }
    void heapify(vector<int>& arr){
        heap = arr;
        for(int i = heap.size()/2 -1; i< 0; i--){
            bubbleDown(i);
        }
    }
    void print(){
        cout << "Heap Array: ";
        for(int val: heap){
            cout << val << " ";
            cout << endl;
        }
    }
    MinHeap(vector<int> &arr)
    {
        heapify(arr);
    }
};

