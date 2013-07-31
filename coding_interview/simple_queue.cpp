/**
    Simple implementation of a queue (FIFO) using a singly linked list.
    (c) Duong Nguyen
    Email: ntduong268(@)gmail.com

    For a better implementation, check out queue in C++ STL, etc.
    A C++ STL list can be used to implemented a queue, with front, back, etc.
*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<list>
using namespace std;

struct Node{
    int val;
    Node *next;
};

class MyQueue{
    Node *head, *tail;
    int sz;
public:
    MyQueue(){
        head = tail = NULL;
        sz = 0;
    }

    bool empty(){
        return sz == 0;
    }

    void push(int val){
        Node *new_node = new Node;
        new_node->val = val;
        new_node->next = NULL;
        if(empty()) head = tail = new_node;
        else{ // insert at tail
            tail->next = new_node;
            tail = new_node;
        }
        sz++;
    }

    void pop(){
        if(empty()){
            cerr << "Queue is empty";
            return;
        }
        Node *tmp = head;
        head = head->next;
        delete tmp;
        tmp = NULL;
        sz--;
    }

    int top(){
        if(empty()){
            cerr << "Queue is empty";
            exit(1);
        }
        return head->val;
    }

    void print(){
        if(empty()){
            cout << "Empty\n";
            return;
        }
        Node *cur = head;
        while(cur != NULL){
            cout << cur->val << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

int main(){
    MyQueue my_queue;
    int a[] = {1,2,10,-5};
    for(int i = 0; i < sizeof(a)/sizeof(int); i++){
        my_queue.push(a[i]);
    }
    my_queue.print();
    while(!my_queue.empty()){
        int top = my_queue.top();
        cout << "Current top is: " << top << endl;
        my_queue.pop();
        my_queue.print();
    }
    return 0;
}
