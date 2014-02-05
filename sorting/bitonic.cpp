/**
    Bitonic sort algorithm in recursive way
    Time complexity: O(n x logn^2). This algorithm can be parallelized efficiently.
    In this simple implementation, assume that the size of input is power of 2.
    If it is not the case, we just add the smallest value in the original input until the size becomes
    the nearest (upper) power of 2.

    (c) Duong Nguyen ntduong268(@)gmail.com

*/
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<limits>
#include<vector>

using namespace std;
const int MAXN = 100;

void myswap(int& a, int& b){
    a ^= b;
    b ^= a;
    a ^= b;
}

// Bitonic merge a[i..i+sz*2)
void merge_up(vector<int>& a, int i, int sz){
    if(sz == 0) return;
    for(int j = 0; j < sz; j++){
        if(a[i+j] > a[i+j+sz]) swap(a[i+j], a[i+j+sz]);
    }
    // After the for loop above, a[i..i+sz) << a[i+sz..i+sz*2)
    // and each is a bitonic sequence. Next, merge recursively.
    merge_up(a, i, sz/2);
    merge_up(a, i+sz, sz/2);
}

void merge_down(vector<int>& a, int i, int sz){
    if(sz == 0) return;
    for(int j = 0; j < sz; j++){
        if(a[i+j] < a[i+j+sz]) swap(a[i+j], a[i+j+sz]);
    }
    // After the for loop above, a[i..i+sz) << a[i+sz..i+sz*2)
    // and each is a bitonic sequence. Next, merge recursively.
    merge_down(a, i, sz/2);
    merge_down(a, i+sz, sz/2);
}

/**
    Bitonic sort a[i..i+sz) in given order
    Default order (true): ascending
    Set order = false for descending
*/
void bitonic_sort(vector<int>& a, int i, int sz, bool order=true){
    if(sz == 1) return;
    // build bitonic sequence
    bitonic_sort(a, i, sz/2, true);
    bitonic_sort(a, i+sz/2, sz/2, false);
    // sort by bitonic merge
    if(order) merge_up(a, i, sz/2);
    else merge_down(a, i, sz/2);
}

int get_msb(int n){
    return n ? sizeof(n)*8 - __builtin_clz(n) - 1 : numeric_limits<int>::min();
}

// Find the smallest i s.t 2^i >= n > 2^{i-1}
int find_power2(int n){
    int ans = get_msb(n);
    if((ans == numeric_limits<int>::min()) || ((1 << ans) == n)) return ans;
    else return ans+1;
}

bool is_power_2(int n){
    if(n == 0) return false;
    n -= (n & ~(n-1));
    return (n == 0);
}

int main(){
    ios::sync_with_stdio(false);

    srand(time(NULL));
    int n;
    cin >> n;

    vector<int> a;
    int v, minv;
    for(int i = 0; i < n; i++){
        v = rand() % n;
        if(i == 0) minv = v;
        else minv = min(minv, v);
        a.push_back(v);
    }

    if(!is_power_2(n)){
        int p = find_power2(n);
        for(int j = n; j < (1 << p); j++){
            a.push_back(minv);
        }
    }

    cout << "Before sorting:\n";
    for(int i = 0; i < a.size(); i++) cout << a[i] << " ";
    cout << endl;
    cout << "Bitonic sorting...\n";
    bitonic_sort(a, 0, a.size());
    cout << "After sorting:\n";
    for(int i = 0; i < a.size(); i++) cout << a[i] << " ";
    cout << endl;

    return 0;
}
