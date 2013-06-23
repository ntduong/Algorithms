#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int kth_smallest(vector<int>& a, int k){
	int l = 0, u = (int)a.size()-1;
	while(l < u){
		int i = l;
		int j = u;
		int x = a[k];
		while(i <= k && j >= k){
			while(a[i] < x) i++;
			while(a[j] > x) j--;
			swap(a[i],a[j]);
			i++;
			j--;
		}
		if(j < k) l = k;
		if(i > k) u = j;
	}
	return a[k];
}
