/**
    Find the most significant bit if a given number n >= 0.
    In other word, find the largest i such that 2^i <= n
    (c) Duong Nguyen
*/

#include<iostream>
#include<limits>
using namespace std;

// n = 0, then for any i \in Z, 2^i >= n. In this case, answer is -INF
int msb_v1(int n){
    return n ? sizeof(n)*8 - __builtin_clz(n) - 1 : numeric_limits<int>::min();
}

int msb_ull(unsigned long long n){
    return n ? sizeof(n)*8 - __builtin_clzll(n) - 1 : numeric_limits<unsigned long long>::min();
}

int msb_v2(unsigned x){
    union {
        double v;
        int b[2];
    };

    v = x; // store x as double (8 bytes = 64 bits) in v
    return (b[1] >> 20) - 1023; // obtain the exponent part
}


int main(){
    cout << msb_v1(n) << endl;
    cout << msb_v2(n) << endl;

    return 0;
}
