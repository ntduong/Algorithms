#include<cstdio>
#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;

bool is_open(char c){
    return (c == '(' || c == '[' || c == '{');
}

bool is_close(char c){
    return (c == ')' || c == ']' || c == '}');
}

bool is_match(char c1, char c2){
    if(c1 == '(' && c2 == ')') return true;
    if(c1 == '[' && c2 == ']') return true;
    if(c1 == '{' && c2 == '}') return true;
    return false;
}

bool check(const string & seq){
    int len = (int) seq.length();
    stack<char> a_stack;
    int i;
    for(i = 0; i < len; i++){
        if(is_open(seq[i])) a_stack.push(seq[i]);
        else if(is_close(seq[i])){
            if(a_stack.empty()) return false;
            char atop = a_stack.top();
            a_stack.pop();
            if(!is_match(atop, seq[i])) return false;
        }
    }

    return a_stack.empty() && (i == len);
}

const int N_CASES = 6;
void test(){
    string in[] = {"(())", "({[]})", "(", "]", "", "{[}]"};
    bool out[] = {true, true, false, false, true, false};
    for(int i = 0; i < N_CASES; i++){
        if(check(in[i]) != out[i]) cout << "Case #" << i << ": FAILED" << endl;
        else cout << "Case #" << i << ": PASSED" << endl;
    }
}

int main(){
    test();
    return 0;
}
