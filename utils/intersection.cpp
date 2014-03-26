/**
    Compute the intersection of two sets A, B of sizes n, m respectively.
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// O(m+n) solution, good when m ~ n
vector<int> intersect_1(const vector<int>& A, const vector<int>& B){
    vector<int> res;
    int i = 0, j = 0;
    while(i < A.size() && j < B.size()) {
        if(A[i] == B[j] && (i == 0 || A[i] != A[i-1])){
            res.push_back(A[i]);
            ++i, ++j;
        } else if(A[i] < B[j]){
            ++i;
        } else { // A[i] > B[j]
            ++j;
        }
    }
    return res;
}

// O(nlogm) assumed that n << m, nlogm < mlogn
vector<int> intersect_2(const vector<int>& A, const vector<int>& B){
    vector<int> res;
    for(int i = 0; i < A.size(); ++i){
        if((i == 0) || (A[i] != A[i-1]) && binary_search(B.cbegin(), B.cend(), A[i])){
            res.push_back(A[i]);
        }
    }

    return res;
}

int main() {
    return 0;
}
