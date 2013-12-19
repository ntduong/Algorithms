/**
    Implementation of 1-based Binary Indexed Tree (BIT).
    Test in Codeforces Round 220 Div2 Problem D: Inna and Sequence
    (c) Duong Nguyen
*/
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

//1-based BIT [1,n]
template<class T>
struct BIT {
    int n;
    vector<T> data;
    BIT(int n):n(n){
        data = vector<T>(n+1);
    }

    void add(int i, T x){
        while(i <= n){
            data[i] += x;
            i += (i & -i);
        }
    }

    // sum up to i: [1,i]
    T sum(int i){
        T s = 0;
        while(i > 0){
            s += data[i];
            i -= (i & -i);
        }
        return s;
    }

    // sum [l,r]
    T sum_range(int l, int r){
        if(l == 1) return sum(r);
        else return sum(r)-sum(l-1);
    }
};

int a[1000005];

#define MYTEST

int main(){
#ifdef MYTEST
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) scanf("%d", a+i);

    BIT<int> f(n);
    vector<short> V;
    int t;
    for(int i = 0; i < n; i++){
        scanf("%d", &t);
        if(t == -1){
            int cur_len = f.sum_range(1, n);
            int p = upper_bound(a, a+m, cur_len)-a; // first p such that a[p] > cur_len
            while(p--){
                //binary search to find remove place
                int lo = 0, hi = n;
                while(lo+1 < hi){
                    int mid = (lo+hi)/2;
                    if(f.sum_range(1, mid) >= a[p]) hi = mid;
                    else lo = mid;
                }
                f.add(hi, -1); // remove
            }
        } else{
            f.add(V.size()+1, 1);
            V.push_back(t);
        }
    }

    vector<char> ans;
    for(int i = 0; i < (int)V.size(); i++){
        if(f.sum_range(i+1,i+1)) ans.push_back('0'+V[i]);
    }

    if(ans.empty()) cout << "Poor stack!";
    else{
        for(int i = 0; i < ans.size(); i++) cout << ans[i];
    }
    return 0;
}
