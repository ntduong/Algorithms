#include<cstdio>
#include<iostream>
using namespace std;

void print(int a[], int n){
	for(int i = 0; i < n; i++) cout << a[i] << " ";
	cout << "\n";
}

void select_sort(int a[], int n){
	for(int i = 0; i < n-1; i++){
		int ith_min = i;
		for(int j = i+1; j < n; j++){
			if(a[j] < a[ith_min]) ith_min = j;
		}
		if(ith_min != i){
			int tmp = a[i];
			a[i] = a[ith_min];
			a[ith_min] = tmp;
		}
	}
}

int main(){
	int a[4] = {4,3,2,1};
	select_sort(a, 4);
	print(a, 4);
	return 0;
}
