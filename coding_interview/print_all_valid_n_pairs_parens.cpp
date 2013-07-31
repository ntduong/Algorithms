// 9.6 CTCI
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<set>

using namespace std;

void addParen(vector<string> &ans, int leftRem, int rightRem, string s){
    if(leftRem < 0 || rightRem < leftRem) return; //invalid cases
    if(leftRem == 0 && rightRem == 0){
        ans.push_back(s);
        s = "";
    } else{
        if(leftRem > 0){
            s += '(';
            addParen(ans, leftRem-1, rightRem, s);
        }
        if(rightRem > leftRem){
            s += ')';
            addParen(ans, leftRem, rightRem-1, s);
        }
    }
}

vector<string> generateParens(int count){
    vector<string> ans;
    string tmp = "";
    addParen(ans, count, count, tmp);
    return ans;
}

////////////////////////////
string insertInside(string str, int left_ind){
    string left = str.substr(0, left_ind+1);
    string right = str.substr(left_ind+1);
    return left + "()" + right;
}

set<string> generateParens2(int rem){
    set<string> ans;
    if(rem == 0) ans.insert("");
    else{
        set<string> prev = generateParens2(rem-1);
        set<string>::iterator it;
        for(it = prev.begin(); it != prev.end(); it++){
            string str = *it;
            for(int i = 0; i < str.length(); i++){
                if(str[i] == '('){
                    string s = insertInside(str, i);
                    ans.insert(s);
                }
            }
            if(ans.find("()"+str) == ans.end()) ans.insert("()"+str);
        }

    }
    return ans;
}

int main(){
    /*
    vector<string> ans = generateParens(2);
    vector<string>::iterator it;
    for(it = ans.begin(); it != ans.end(); it++)
        cout << *it << endl;
    */

    set<string> ans = generateParens2(3);
    set<string>::iterator it;
    for(it = ans.begin(); it != ans.end(); it++) cout << *it << endl;
    return 0;
}
