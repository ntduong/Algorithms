#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;

void* align_malloc(size_t required_bytes, size_t alignment){
    void *p1; // point to the original block
    void **p2; // point to aligned part
    int offset = alignment - 1 + sizeof(void*);
    p1 = (void*) malloc(required_bytes + offset);
    if(p1 == NULL){
        cerr << "Cannot allocate memory";
        exit(1);
    }
    p2 = (void**) (((size_t) (p1) + offset) & ~(alignment-1));
    p2[-1] = p1; // we need p1 to free
    return p2;
}

void align_free(void *p2){
    void *p1 = ((void**)p2)[-1];
    free(p1);
}


int main(){
    return 0;
}
