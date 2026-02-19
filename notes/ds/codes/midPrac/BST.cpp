#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    Node *leftChild;
    Node *rightChild;
    int val;
    Node *parent;
    int height;

    Node(int value)
    {
        val = value;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = nullptr;
        height = 0;
    }
    Node()
    {
        val = 0;
        leftChild = rightChild = parent = nullptr;
        height = 0;
    }
};

class BST
{

public:
    Node *root;
    BST()
    {
        root = nullptr;
    }
    void printTreeInorder(Node *root)
    {
        if (!root)
        {
            cout << "Tree Empty" << endl;
            return;
        }
        if (root->leftChild)
        {
            printTreeInorder(root->leftChild);
        }
        cout << root->val << " ";
        if(root->rightChild){
            printTreeInorder(root->rightChild);
        }
    }

    void insert(int value){
        Node* newNode = new Node(value);
        if(!root){
            root = newNode;
            printTreeInorder(root);
            return;
        }
        Node* curr = root;
        Node* par = nullptr;
        while(curr!=nullptr){
            par = curr;
            if(curr->val < value){
                curr = curr->rightChild;
            } else {
                curr = curr->leftChild;
            }
        }
        newNode->parent = par;
        if(value<par->val){
            par->leftChild = newNode;
        } else{
            par->rightChild = newNode;
        }

        updateHeight(par);
        printTreeInorder(newNode);
    }
    void updateHeight(Node* node){
        while(node!=nullptr){
            int leftH = node->leftChild ? node->leftChild->height : -1;
            int rightH = node->rightChild ? node->rightChild->height : -1;
            int newH = max(leftH, rightH) + 1;
            if(node->height==newH){
                break;
            }
            node->height = newH;
            node = node->parent;
        }
    }
    void search(int key){
        
        if(!root){
            cout<< "Tree empty, no such node found" << endl;
        }
        Node *curr = root;
        while(curr){
            if (curr->val > key)
            {
                curr = curr->leftChild;
            }
            else if (curr->val < key)
            {
                curr = curr->rightChild;
            }
            else if (curr->val == key)
            {
                cout << "Node found" << endl;
                cout << "Node details: " << endl;
                cout << "Node height : " << curr->height;
            }
        }
        cout << "No such node present" << endl;
    }
    void getHeight(int value){
        // already coovered
    }
    void beforeAfter(int value){
        
    }
};

int main()
{
    return 0;
}