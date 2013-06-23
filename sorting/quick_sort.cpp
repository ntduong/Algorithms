#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<ctime>
using namespace std;

void my_qsort(int a[], int le, int ri){
	if(le >= ri) return;
	int p_ind = rand() % (ri-le+1) + le;
	int pivot = a[p_ind];
	int i = le, j = ri;
	while(1){
		while(a[i] < pivot && i <= ri) i++;
		while(a[j] > pivot && j >= le) j--;
		if(i > j) break;
		if(i <= j){
			if(i < j){
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
			i++, j--;
		}
	}
	my_qsort(a, le, j);
	my_qsort(a, i, ri);
}

int main(){
	int a[7] = {10,1,9,3,2,5,6};
	my_qsort(a, 0, 6);
	for(int i = 0; i < 7; i++) cout << a[i] << " ";
	cout << "\n";
	return 0;
}
