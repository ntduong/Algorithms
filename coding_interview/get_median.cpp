#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

priority_queue<int> low; // max-heap for lower part
priority_queue<int, vector<int>, greater<int> > up; // min-heap for upper part

// invariant: #|low| <= #|up| <= #|low| + 1
void add_number(int n){
    if(up.size() == low.size()){
        if(!up.empty() && up.top() < n){
            low.push(up.top());
            up.pop();
            up.push(n);
        }
        else{
            low.push(n);
        }
    }
    else{ // #|low| = #|up| + 1
        if(n < low.top()){
            up.push(low.top());
            low.pop();
            low.push(n);
        }
        else{
            up.push(n);
        }
    }
}

int get_median(){
    if(low.empty()) return 0; // both are empty given the invariant
    if(low.size() == up.size()){
        return ((double) low.top() + (double) up.top())/2;
    }
    else{
        return low.top();
    }
}

int main(){
    int a[] = {1,3,5,-2,10};
    for(int i = 0; i < 5; i++){
        add_number(a[i]);
        cout << "Median:" << get_median() << endl;
    }
    return 0;
}
