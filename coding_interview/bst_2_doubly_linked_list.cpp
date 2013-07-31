#include<cstdio>
#include<iostream>

using namespace std;

struct node{
    int val;
    struct node* small;
    struct node* large;
};

// Join a and b such that b is right after a
void join(node* a, node* b){
    a->large = b;
    b->small = a;
}

// Join two doubly linked lists
node* append(node* a, node* b){
    node* a_last, *b_last;
    if(a == NULL) return b;
    if(b == NULL) return a;
    a_last = a->small;
    b_last = b->small;

    join(a_last, b);
    join(b_last, a);
    return a;
}

node* bst2list(node* root){
    node* left_list, *right_list;
    if(root == NULL) return NULL;

    //recursive calls on left and right children of root
    left_list = bst2list(root->small);
    right_list = bst2list(root->large);

    // Make length 1 doubly linked list from root
    root->small = root;
    root->large = root;

    //Join all
    left_list = append(left_list, root);
    left_list = append(left_list, right_list);
    return left_list;
}


int main(){


    return 0;
}
