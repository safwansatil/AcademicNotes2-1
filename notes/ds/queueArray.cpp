#include <bits/stdc++.h>
using namespace std;

class QueueArray{
    int size;
    int front, rear;
    int* arr;

    public:
    QueueArray(int size){
        this->size = size;
        this->arr = new int[size];
        this->front = 0;
        this->rear = -1;
    }
    void enqueue(int x){
        if(rear == size-1){
            cout << "Queue Overflow" << endl;
            return;
        }
        rear++;
        arr[rear] = x;
    }
    int dequeue(){
        if(front>rear){
            cout << "Queue Empty" << endl;
            return -1;
        }
        int item = arr[front];
        for(int i=front; i<rear; i++){
            arr[i] = arr[i+1];
        }
        rear--;
        return item;
    }
};