#include <iostream>
using namespace std;

// Node structure
struct Node
{
    int data;
    Node *next;

    Node(int val) : data(val), next(nullptr) {}
};

class LinkedListStack
{
private:
    Node *top;
    int stackSize;

public:
    LinkedListStack() : top(nullptr), stackSize(0) {}

    void push(int x)
    {
        Node *newNode = new Node(x);
        newNode->next = top;
        top = newNode;
        stackSize++;
        cout << x << " pushed to stack\n";
    }

    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow\n";
            return -1;
        }
        Node *temp = top;
        int popped = top->data;
        top = top->next;
        delete temp;
        stackSize--;
        cout << popped << " popped from stack\n";
        return popped;
    }

    int peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
            return -1;
        }
        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    int size()
    {
        return stackSize;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
            return;
        }
        cout << "Stack (top to bottom): ";
        Node *current = top;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Bonus: Reverse the stack
    void reverse()
    {
        if (isEmpty() || top->next == nullptr)
            return;

        Node *prev = nullptr, *current = top, *next = nullptr;
        while (current != nullptr)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        top = prev;
        cout << "Stack reversed\n";
    }

    ~LinkedListStack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
};

int main()
{
    LinkedListStack s;
    s.push(5);
    s.push(15);
    s.push(25);

    cout << "Top: " << s.peek() << endl;
    cout << "Size: " << s.size() << endl;

    s.display();

    s.reverse();
    s.display();

    s.pop();
    s.pop();

    cout << "Is empty? " << (s.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}