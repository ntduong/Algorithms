/**
    Implementation of a queue using two stacks
    (c) Duong Nguyen
    Email: ntduong268(@)gmail.com

    Todo: Test :)
*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;

class QueueBy2Stack{
    stack<int> newest, oldest;
    void shift_stacks(){
        if(oldest.empty()){
            while(!newest.empty()){
                oldest.push(newest.top());
                newest.pop();
            }
        }
    }

public:
    int sz() const{
        return newest.size() + oldest.size();
    }

    bool empty(){
        return sz() == 0;
    }

    void push(int val){
        newest.push(val);
    }

    int top(){
        if(empty()){
            cerr << "Queue is empty";
            exit(1);
        }
        shift_stacks();
        return oldest.top();
    }

    void pop(){
        if(empty()){
            cerr << "Queue is empty";
            return;
        }
        shift_stacks();
        oldest.pop();
    }
};

int main(){
    return 0;
}
