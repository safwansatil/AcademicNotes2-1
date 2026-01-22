#include <bits/stdc++.h>
using namespace std;

class MaxHeap
{
private:
    vector<int> heap;
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i)
    {
        return 2 * i + 1;
    }
    int rightChild(int i)
    {
        return 2 * i + 2;
    }
    void bubbleUp(int i)
    {
        while (i > 0 && heap[i] > heap[parent(i)])
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void bubbleDown(int i)
    {
        int l = leftChild(i);
        int r = rightChild(i);
        int n = heap.size();
        int largest = i;
        if (l < n && heap[l] > heap[largest])
        {
            largest = l;
        }
        if (r < n && heap[r] > heap[largest])
        {
            largest = r;
        }
        if (largest != i)
        {
            swap(heap[largest], heap[i]);
            bubbleDown(largest);
        }
    }

public:
    void push(int i)
    {
        heap.push_back(i);
        bubbleUp(heap.size() - 1);
    }
    int pop()
    {
        if (heap.empty())
        {
            return -1;
        }
        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
        {
            bubbleDown(0);
        }
        return root;
    }
    void heapify(vector<int> &arr)
    {
        heap = arr;
        for (int i = heap.size() / 2 - 1; i >= 0; i--)
        {
            bubbleDown(i);
        }
    }
};

void heapSort(vector<int> &arr)
{
    MaxHeap h;
    h.heapify(arr);
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i] = h.pop();
    }
}

int main()
{
    return 0;
}