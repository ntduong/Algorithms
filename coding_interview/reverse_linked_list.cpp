#include<cstdio>
#include<iostream>
#include<algorithm>

using namespaces std;

typedef struct Node{
    int val;
    struct Node *next;
} Node;

static void reverse(Node** head_ref){
    Node* res = NULL;
    Node* cur = *head_ref;
    Node* next;

    while(cur != NULL){
        next = cur->next;
        cur->next = res;
        res = cur;
        cur = next;
    }
    *head_ref = res;
}

int main(){
    // test code
    return;
}
