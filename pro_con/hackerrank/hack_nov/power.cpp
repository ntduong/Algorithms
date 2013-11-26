#include<cstdio>
#include<iostream>
using namespace std;

typedef long long ll;

bool is_prime(int N){
    if(N == 2) return true;
    if(N < 2 || N % 2 == 0) return false;
    for(int i = 3; i*i <= N; ++i){
        if(N % i == 0) return false;
    }
    return true;
}

ll mod_pow(ll x, ll n, ll mod){
    ll res = 1;
    while(n > 0){
        if(n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

ll bigmod(string x, ll mod){
    ll res = 0;
    int len = (int)x.length();
    for(int i = 0; i < len; i++){
        int d = x[i] - '0';
        res = res * 10 % mod;
        res = (res + d) % mod;
    }
    return res;
}

int main(){
    int T;
    ll mod = 1000000007;
    string a, b;
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t){
        cin >> a >> b;
        ll x = bigmod(a, mod);
        ll y = bigmod(b, mod-1);
        cout << mod_pow(x, y, mod) << endl;
    }

    return 0;
}
