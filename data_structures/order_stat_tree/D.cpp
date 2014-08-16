/**
    Example of order stat tree: Codeforces #261 D
    Given {a_i}_{i=1}^n. Define f(l,r,x) as # {a_i s.t. l <= i <= r and a_i = x}
    Find all pairs (i,j) s.t., 1 <= i < j <= n, and f(1,i,a_i) > f(j,n,a_j).
    Constraint: n <= 10^6, then O(n^2) solution should be TLE.

    Written by Duong Nguyen
*/

#include<cstdio>
#include<iostream>
#include<map>
#include<algorithm>
#include<cassert>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

const int MAXN = static_cast<int>(1e6);

typedef pair<int,int> ii;
typedef
tree<
    ii,
    null_type,
    less<ii>,
    rb_tree_tag,
    tree_order_statistics_node_update
> set_t;

int a[MAXN+1];
int L[MAXN+1], R[MAXN+1];

//#define SUBMIT
int main(){
#ifndef SUBMIT
    freopen("in.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#endif // SUBMIT

    int n;
    cin >> n;

    map<int, int> cnt[2];

    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }

    for(int i = 0; i < n; ++i){
        L[i] = ++cnt[0][a[i]];
        R[n-i-1] = ++cnt[1][a[n-i-1]];
    }

    uint64_t ans = 0;
    set_t S;
    for(int i = 1; i < n; ++i){
        S.insert(ii(L[i-1], i-1));
        ans += i - S.order_of_key(ii(R[i], i));
    }

    cout << ans;
    return 0;
}
