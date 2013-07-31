/**
    Simple implementation of stack with a vector/an array
    (c) Duong Nguyen
    Email: ntduong268(@)gmail.com
*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>
#include<limits>
#include<cassert>
using namespace std;

struct Node{
    int val, minv;
};

// Implementation of a stack with min feature in O(1)
class StackWithMin{
    vector<Node*> buf;
public:
    int sz() const{
        return (int) buf.size();
    }

    bool empty() const{
        return sz() == 0;
    }

    int get_min() const{
        if(empty()) return numeric_limits<int>::max(); // Error value
        return get_top()->minv;
    }

    void push(int val){
        Node *new_node = new Node;
        new_node->val = val;
        int new_min = min(get_min(), val);
        new_node->minv = new_min;
        buf.push_back(new_node);
    }

    bool pop(){
        if(empty()) return false; // Pop from an empty stack
        Node *tmp = get_top();
        buf.pop_back();
        delete tmp;
        return true;
    }

    Node* get_top() const{
        if(empty()) return NULL;
        return buf.back();
    }

    void print() const{
        if(empty()){
            cout << "Empty\n";
            return;
        }
        vector<Node*>::const_iterator it;
        for(it = buf.begin(); it != buf.end(); it++)
            cout << "(" << (*it)-> val << ", " << (*it)->minv << ") ";
        cout << endl;
    }
};

/**
    Simple stack using a fixed-size array
*/

const int FIXED_SIZE = 100;
class MyStack{
    int *buf;
    int top, sz;
public:
    MyStack(){
        sz = FIXED_SIZE;
        buf = new int[sz];
        top = -1;
    }
    MyStack(int sz){
        sz = sz;
        buf = new int[sz];
        top = -1;
    }
    ~MyStack(){
        delete [] buf;
        buf = NULL;
    }

    int get_size() const{
        return top+1;
    }

    void print() const{
        if(empty()){
            cout << "Empty\n";
            return;
        }
        for(int i = 0; i <= top; i++) cout << buf[i] << " ";
        cout << endl;
    }

    void push(int val){
        if(top+1 >= sz){
            cerr << "Stack is full!";
            return;
        }
        buf[++top] = val;
    }

    void pop(){
        if(top == -1){
            cerr << "Stack is empty!";
            return;
        }
        top--;
    }

    int get_top(){
        if(top == -1){
            cerr << "Stack is empty!";
            exit(1);
        }
        return buf[top];
    }

    bool empty() const{
        return top == -1;
    }
};

int main(){
    //StackWithMin my_stack;
    MyStack my_stack;
    int a[] = {4, 5, -2, 10, 1};
    for(int i = 0; i < sizeof(a)/sizeof(int); i++){
        my_stack.push(a[i]);
    }
    my_stack.print();
    while(!my_stack.empty()){
        my_stack.pop();
        my_stack.print();
    }
    return 0;
}
