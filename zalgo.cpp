#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

/*
	Compute Z array
	Z[i] := the length of the longest substring starting from s[i] which is also a prefix of S
	O(n)
	Application: standard string matching problem.
				 Codeforces R93 B
				 Interviewstreet: String similarity
*/

vector<int> zalgo(const string& s){
	int len = s.size();
	int ans = len, L = 0, R = 0;
	vector<int> z(len, 0);
	for(int i = 1; i < len; i++){
		if(i > R){
			L = R = i;
			while(R < len && s[R-L] == s[R]) R++;
			z[i] = R-L;
			R--;
		}else{
			int k = i-L;
			if(z[k] < R-i+1) z[i] = z[k];
			else{
				L = i;
				while(R < len && s[R-L] == s[R])R++;
				z[i] = R-L;
				R--;
			}
		}
	}
}


int main(){

	return 0;
}
