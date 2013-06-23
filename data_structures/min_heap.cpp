/**
	Simple implementation of min-heap (priority queue)
	(c) Duong Nguyen
	Email: ntduong268@gmail.com

	Note: parent i, left child 2*i+1, right child 2*i+2
*/

#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
using namespace std;
#define MAX_N 100

int heap[MAX_N], sz = 0;

void push(int x){
	if(sz == MAX_N){
		cerr << "Heap is already full!";
		exit(1);
	}

	int i = sz++;
	while(i > 0) {
		int p = (i-1)/2;
		if(heap[p] <= x) break;
		heap[i] = heap[p];
		i = p;
	}
	heap[i] = x;
}

int pop(){
	if(sz == 0){
		cerr << "Heap is empty!";
		exit(1);
	}
	int ret = heap[0]; // return root (smallest number in heap)
	int x = heap[--sz]; // decrease size, take last value to root, then sift down

	int i = 0;
	while(i*2+1 < sz){
		int a = i*2+1, b = i*2+2;
		if(b < sz && heap[b] < heap[a]) a = b; // a is the smallest child
		if(heap[a] >= x) break; // satisfy heap property --> finish sift-down
		heap[i] = heap[a]; // make a (smallest child ) be parent
		i = a;
	}
	heap[i] = x;
	return ret;
}

bool is_empty(){
	return sz == 0;
}

bool is_full(){
	return sz == MAX_N;
}

void print(int i, int depth=0){
	if(i*2+1 < sz) print(i*2+1, depth+5);
	if(i < sz) cout << "\n" << string(depth, ' ') << heap[i];
	if(i*2+2 < sz) print(i*2+2, depth+5);
}

int test(){
	int val[10] = {100, 2, 20, 1, 3, 4, 5, -2, 9, 6};
	for(int i = 0; i < 10; i++){
		push(val[i]);
	}
	print(0);
	cout << endl;
	while(!is_empty()){
		int val = pop();
		cout << val << " ";
	}
	cout << endl;
	print(0);
}

int main(){
	test();
	return 0;
}
