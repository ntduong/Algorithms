#include<iostream>
#include<string>
#include<algorithm>
#include<memory>
#include<queue>

using namespace std;

struct Symbol {
    char c;
    double prob;
    string code;
};

struct BinaryTree {
    double prob;
    Symbol* sb; // if this is nullptr -> internal node, otherwise leaf node
    shared_ptr<BinaryTree> left, right;
};

struct Compare {
    bool operator() (const shared_ptr<BinaryTree>& lhs, const shared_ptr<BinaryTree>& rhs) const {
        return lhs->prob > rhs->prob; // min-heap using C++ priority_queue
    }
};

// Assign code starting from the root, plus 0 if going left, 1 if going right
void assign_code(const shared_ptr<BinaryTree>& r, const string& s){
    if(r){
        if(r->sb){ // leaf node containing a symbol
            r->sb->code = s;
        } else{
            assign_code(r->left, s+'0');
            assign_code(r->right, s+'1');
        }
    }
}

void huffman_encoding(vector<Symbol>* symbols) {
    priority_queue<shared_ptr<BinaryTree>,
                   vector<shared_ptr<BinaryTree> >,
                   Compare> min_heap;

    for(auto& s : *symbols){
        min_heap.emplace(new BinaryTree{s.prob, &s, nullptr, nullptr});
    }

    while(min_heap.size() > 1){
        shared_ptr<BinaryTree> l = min_heap.top();
        min_heap.pop();
        shared_ptr<BinaryTree> r = min_heap.top();
        min_heap.pop();
        min_heap.emplace(new BinaryTree{l->prob+r->prob, nullptr, l, r});
    }

    assign_code(min_heap.top(), string());
}

int main(){
    return 0;
}
