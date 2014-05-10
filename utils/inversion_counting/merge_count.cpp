/**
    Counting inversion by divide-and-conquer approach
    O(nlogn) time, O(n) space
*/

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;

ll merge_count(vector<int>& a){

    ll cnt = 0;
    size_t n = a.size();

    if(n > 1){
        vector<int> lo(a.begin(), a.begin()+n/2);
        vector<int> hi(a.begin()+n/2, a.end());
        cnt += merge_count(lo);
        cnt += merge_count(hi);
        for(int i = 0, lid = 0, hid = 0; i < n; ++i){
            if(hid == hi.size()) a[i] = lo[lid++];
            else if(lid == lo.size()) a[i] = hi[hid++];
            else if(lo[lid] <= hi[hid]){
                a[i] = lo[lid++];
            } else{
                a[i] = hi[hid++];
                cnt += (ll)(n/2-lid);
            }
        }
    }

    return cnt;
}

int main(){

    freopen("IntegerArray.txt", "r", stdin);
    vector<int> a;
    int n;
    while(cin >> n){
        a.push_back(n);
    }
    cout << merge_count(a);
    return 0;
}
