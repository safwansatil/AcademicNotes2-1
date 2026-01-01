#include <bits/stdc++.h>
using namespace std;
class CircularQueue
{
private:
    int *arr;
    int front, rear;
    int capacity;
    int size; // track current elements

public:
    CircularQueue(int cap)
    {
        capacity = cap;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }

    void enqueue(int x)
    {
        if (size == capacity)
        {
            cout << "Queue Full!\n";
            return;
        }
        rear = (rear + 1) % capacity; // Wrap around
        arr[rear] = x;
        size++;
    }

    int dequeue()
    {
        if (size == 0)
        {
            cout << "Queue Empty!\n";
            return -1;
        }
        int item = arr[front];
        front = (front + 1) % capacity; // Wrap around
        size--;
        return item;
    }

    bool isEmpty() { return size == 0; }
    bool isFull() { return size == capacity; }
};