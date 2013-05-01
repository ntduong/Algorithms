#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#define MAXN 65536
#define MAXLG 17
using namespace std;

char A[MAXN];

struct entry{
	int nr[2], p;
} L[MAXN];


/*
	n is the length of input string
	P[k][i] = position of substring A[i...i+2^k-1] in {A[j...j+2^k-1]} for j = 0,n-1
*/
int P[MAXLG][MAXN], n, i, step, cnt;

int cmp(struct entry a, struct entry b){
	return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1] ? 1 : 0) : (a.nr[0] < b.nr[0] ? 1 : 0);
}

void buildSA(){
	for(n = strlen(A), i = 0; i < n; i++){
		P[0][i] = A[i]-'a';
	}

	for(step = 1, cnt = 1; cnt >> 1 < n; step++, cnt <<= 1){
		for(i = 0; i < n; i++){
			L[i].nr[0] = P[step-1][i];
			L[i].nr[1] = i+cnt < n ? P[step-1][i+cnt] : -1;
			L[i].p = i;
		}

		sort(L,L+n,cmp);
		for(i = 0; i < n; i++){
			P[step][L[i].p] = i > 0 && L[i].nr[0] == L[i-1].nr[0] && L[i].nr[1] == L[i-1].nr[1] ? P[step][L[i-1].p] : i;
		}
	}
}

//computing the longest common prefix of two suffixes of A, called Ax and Ay (LCP)
//x and y is the starting indices of suffixes Ax, Ay
int lcp(int x, int y){
	int k, ret = 0;
	if(x == y) return n-x;
	for(k = step-1; k >= 0 && x < n && y < n; k--)
		if(p[k][x] == p[k][y])
			x += 1 << k, y += 1 << k, ret += 1 << k;

	return ret;
}


int main(){
	gets(A);



	return 0;
}
