/**
    Very simple and inefficient suffix tree
    (c) Duong Nguyen; ntduong268(@)gmail.com
*/
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
#include<string>
using namespace std;

struct Node{
    map<char, Node*> children;
    char value;
    vector<int> indexes;
};

void insert_string(string s, int index, Node* root){
    root->indexes.push_back(index);
    if(s.length() > 0){
        char val = s[0];
        root->value = val;
        Node *child;
        if((root->children).find(val) != (root->children).end()){
            child = (root->children)[val];
        }
        else{
            child = new Node;
            (root->children)[val] = child;
        }
        string rem = s.substr(1);
        insert_string(rem, index, child);
    }
}

vector<int> search(string s, Node *root){
    if(s.length() == 0) return root->indexes;
    else{
        char val = s[0];
        if((root->children).find(val) != (root->children).end()){
            string rem = s.substr(1);
            return search(rem, (root->children)[val]);
        }
    }
    return vector<int>(); // NOT FOUND
}

vector<int> search_tree(string s, Node* root){
    return search(s, root);
}

int main(){
    Node *root = new Node;
    string s = "I am just a newbie in the algorithm wonderland!";
    for(int i = 0; i < s.length(); i++){
        string suffix = s.substr(i);
        insert_string(suffix, i, root);
    }

    vector<int> ret = search_tree("n", root);
    vector<int>::iterator it;
    for(it = ret.begin(); it != ret.end(); it++) cout << *it << endl;

    return 0;
}
