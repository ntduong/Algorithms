/**
	Heap sort with max-heap
	(c) Duong Nguyen
*/

#include<cstdio>
#include<iostream>
using namespace std;
#define MAX_N 100

void sift_down(int *a, int start_node, int end_node){
	int x = a[start_node];
	while(start_node*2+1 <= end_node){
		int child = start_node*2+1;
		if(child+1 <= end_node && a[child] < a[child+1]) child++;
		if(x >= a[child]) break;
		a[start_node] = a[child];
		start_node = child;
	}
	a[start_node] = x;
}

void heap_sort(int *a, int n){
	for(int i = n/2; i >= 0; i--) sift_down(a, i, n-1); // make max-heap
	for(int i = n-1; i >= 1; i--){
		int tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;

		sift_down(a, 0, i-1);
	}

}

void test(){
	int a[9] = {-1, 2, 4, -2, 40, 5, 8, 7, 2};
	heap_sort(a, 9);
	for(int i = 0; i < 9; i++) cout << a[i] << " ";
	cout << endl;
}

int main(){
	test();
	return 0;
}
