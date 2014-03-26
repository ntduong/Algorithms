/**
    Three sum problem:
        Given an array A[0...n-1] and an integer S (>0),
        find 0<= i,j,k <= n-1 s.t A[i]+A[j]+A[k] = S, or report there doesn't exist such triplet

    Todo: How can we generalize the problem to k-sum?
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<tuple>
using namespace std;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;


// Find 0 <= i, j <= n-1, such that A[i] + A[j] = s
// given that A is sorted, O(n) algorithm using two-pointer technique
ii find_2_sum(const vector<int>& A, int s){
    int le = 0, ri = A.size()-1;
    while(le <= ri){
        if(A[le] + A[ri] > s){
            --ri;
        } else if(A[le] + A[ri] < s){
            ++le;
        } else {
            return make_pair(le, ri);
        }
    }
    return make_pair(-1,-1); // not found!
}

// O(n^2) algorithm
iii find_3_sum(vector<int>& A, int S){
    sort(A.begin(), A.end());
    for(int i = 0; i < A.size()-1; ++i){
        ii p = find_2_sum(A, S-A[i]);
        if(p.first != -1 && p.second != -1){
            return make_tuple(i, p.first, p.second);
        }
    }

    return make_tuple(-1,-1,-1); // not found;
}

int main() {

    return 0;
}
