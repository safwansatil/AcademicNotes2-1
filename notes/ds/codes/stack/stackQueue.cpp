#include <iostream>
using namespace std;

#define MAX 1000 // Maximum stack size

class ArrayStack
{
private:
    int topIndex;
    int arr[MAX];

public:
    ArrayStack()
    {
        topIndex = -1; // Empty stack
    }

    bool push(int x)
    {
        if (topIndex >= MAX - 1)
        {
            cout << "Stack Overflow\n";
            return false;
        }
        arr[++topIndex] = x;
        cout << x << " pushed to stack\n";
        return true;
    }

    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow\n";
            return 0;
        }
        int x = arr[topIndex--];
        cout << x << " popped from stack\n";
        return x;
    }

    int peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
            return 0;
        }
        return arr[topIndex];
    }

    bool isEmpty()
    {
        return (topIndex < 0);
    }

    int size()
    {
        return topIndex + 1;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
            return;
        }
        cout << "Stack (top to bottom): ";
        for (int i = topIndex; i >= 0; i--)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// Example usage
int main()
{
    ArrayStack s;
    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top element: " << s.peek() << endl;
    cout << "Stack size: " << s.size() << endl;

    s.display();

    s.pop();
    s.pop();

    cout << "Is empty? " << (s.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}