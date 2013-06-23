#include<cstdio>
#include<iostream>
using namespace std;

void print(int a[], int n){
	for(int i = 0; i < n; i++) cout << a[i] << " ";
	cout << "\n";
}

void insert_sort(int a[], int n){
	if(n <= 1) return;
	for(int i = 1; i < n; i++){
		int val = a[i];
		int j = i;
		while(j > 0 && a[j-1] > val) {
			a[j] = a[j-1];
			j--;
		}
		a[j] = val;
	}
}

void insert_sort_with_bin_search(int a[], int n){
	if(n <= 1) return;
	for(int i = 1; i < n; i++){
		int val = a[i];
		int lo = 0, hi = i-1;
		while(lo <= hi){
			int mid = lo + (hi-lo)/2;
			if(a[mid] > val) hi = mid-1;
			else lo = mid+1;
		}
		for(int j = i; j >= lo; j--) a[j] = a[j-1];
		a[lo] = val;
	}
}

int main(){
	int a[5] = {1,2,3,4,5};
	//insert_sort(a, 5);
	insert_sort_with_bin_search(a, 5);
	print(a, 5);
	return 0;
}
