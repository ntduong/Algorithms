/**
    Given a string S of length n, build its suffix array in O(n * logn^2) time.
    For simplicity, consider S consisting only small English letters a-z.
    Bonus: LCP (longest common prefix) computation in O(logn) time.
    Written by Duong Nguyen.

    @Update: Tested with Codeforces R244 (Div2) D: Match & Catch
             http://codeforces.com/contest/427/problem/D

    @Todo: Rewrite into class SuffixArray
           Fix bugs if any
*/

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

typedef pair<int,string> is;
typedef pair<int,int> ii;
const int MAXN = 65536;
const int MAXLG = 17;

// Utilities
struct Entry {
	int nr[2], p;
} L[MAXN];

int cmp(struct Entry a, struct Entry b){
	return a.nr[0] == b.nr[0] ?
            (a.nr[1] < b.nr[1] ? 1 : 0) :
            (a.nr[0] < b.nr[0] ? 1 : 0);
}

// P[k][i] = position of substring S[i : i+2^k-1] in { S[j:j+2^k-1] for j = 0,n-1}
int P[MAXLG][MAXN];

// Build suffix array of given input string S
int buildSA(const string& S){

	size_t n = S.length();
	for(int i = 0; i < n; ++i){
		P[0][i] = S[i]-'a';
	}

    int step, cnt;
	for(step = 1, cnt = 1; (cnt >> 1) < n; step++, cnt <<= 1) { // O(logn)
		for(int i = 0; i < n; ++i) { // O(n)
			L[i].nr[0] = P[step-1][i];
			L[i].nr[1] = i+cnt < n ? P[step-1][i+cnt] : -1;
			L[i].p = i;
		}
		sort(L, L+n, cmp); // O(nlogn)

		for(int i = 0; i < n; ++i) {
			P[step][L[i].p] =  ( (i > 0) && (L[i].nr[0] == L[i-1].nr[0]) &&
                                (L[i].nr[1] == L[i-1].nr[1]) ) ? P[step][L[i-1].p] : i;
		}
	}

	return step;
}

/**
    Compute LCP of two suffixes S[x:end], S[y:end] in O(logn) time.

    @param x, y: starting indices of suffixes
    @param step: final row index in P table
    @param n: length of input string S
*/
int lcp(int x, int y, int step, int n){

	if(x == y) { // Same suffix
        return n-x;
	}

	int ret = 0;
	for(int k = step-1; (k >= 0) && (x < n) && (y < n); --k) {
		if(P[k][x] == P[k][y]){
			x += (1 << k);
			y += (1 << k);
			ret += (1 << k);
		}
    }

	return ret;
}

/**
    Get suffix array of string S as a list (i1, i2),
    i1: index in suffix array
    i2: starting index in S --> S.substr(i2) to obtain the suffix
*/
vector<ii> getSA(const string& S, int& step){

    vector<ii> sa;
    step = buildSA(S);
    for(size_t i = 0; i < S.length(); ++i){
        sa.push_back(ii(P[step-1][i], i));
    }
    sort(sa.begin(), sa.end());
    return sa;
}

int main(){

    string S = "banana";

    auto sa = getSA(S);
    for(const auto& item : sa){
        cout << item.first << ": " << S.substr(item.second) << endl;
    }

    return 0;
}
