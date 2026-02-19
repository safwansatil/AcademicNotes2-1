#include <bits/stdc++.h>
using namespace std;


// implementation
class Node{
    public:
    Node* next;
    int val;
    Node(int val){
        this->val = val;
        this->next = nullptr;
    }
    Node(){
        this->val=0;
        this->next=nullptr;
    }
};


class LinkedList{
    public:
    Node* head;
    Node* insert(Node* head, int key){
        Node* newNode = new Node(key);
        if(head == nullptr){
            return newNode;
        }
        Node* current = head;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = newNode;
        return head;
    }
    Node* traverseToNode(Node* head, int n){
        Node* curr = head;
        if(curr == nullptr) return nullptr;
        while(curr->next && curr->val!=n){
            curr = curr-> next;
            if(curr->val == n){
                return curr;
            }
        }
        return nullptr;
    }
    Node* deleteNode(Node* head, int n){
        Node* curr = head;
        if(!curr) return nullptr;
        if(curr->val == n){
            head = curr->next;
            Node* temp = curr;
            delete curr;
            return temp;
        }
        while(curr->next && curr->next->val != n){
            curr = curr-> next;
        }
        if(curr->next == nullptr) return nullptr;
        Node* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
        return temp;
    }
};