/**
    Atcoder regular contest ARC#033 (2015/01/31)
    Given a polynomial p(x) of degree n and its values at (n+1) points 0,1,...n.
    All the coefficients are integers. Compute p(T) for a given T.

    Lagrange polynomial formula for interpolation.
    See, e.g., http://en.wikipedia.org/wiki/Lagrange_polynomial
*/

#include<bits/stdc++.h>
using namespace std;

// Template for integer modulo M
// Division and inv operations are valid iff M is a prime.
template <int64_t M>
class Mint {
public:
    Mint() : v(0){}
    Mint(int n) : v(n%M) {}

    int64_t get() const {
        return v;
    }

    Mint& operator += (const Mint& o){
        v = (v+o.v) % M;
        return *this;
    }

    Mint& operator -= (const Mint& o){
        v =(v-o.v + M) % M;
        return *this;
    }

    Mint& operator *= (const Mint& o){
        v = (v*o.v) % M;
        return *this;
    }

    // Warning: Only work for prime M!
    Mint& operator /=(const Mint& o){
        return (*this) *= o.inv();
    }

    Mint pow(int p) const {
        Mint k = *this, res = 1;
        while(p > 0){
            if(p & 1) res *= k;
            k *= k;
            p >>= 1;
        }
        return res;
    }

    // Warning: Only work for prime M!
    // M is a prime and (a,M) = 1, find x = inv(a), i.e., ax = 1(mod M)
    // From Fermat's little theorem, a^(M-1) = 1 (mod M) -> inv(a) = a^(M-2) (mod M)
    Mint inv() const {
        return pow(M-2);
    }

private:
    int64_t v;
};

template<int64_t M>
inline Mint<M> operator+(Mint<M> l, const Mint<M>& r){
    return l += r;
}

template<int64_t M>
inline Mint<M> operator-(Mint<M> l, const Mint<M>& r){
    return l -= r;
}

template<int64_t M>
inline Mint<M> operator*(Mint<M> l, const Mint<M>& r){
    return l *= r;
}

template<int64_t M>
inline Mint<M> operator/(Mint<M> l, const Mint<M>& r){
    return l /= r;
}

template<int64_t M>
inline ostream& operator<<(ostream& os, const Mint<M>& r){
    return os << r.get();
}

typedef Mint<1000000007> mint;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<mint> f(n+1);
    for(auto& v : f){
        int t;
        cin >> t;
        v = t;
    }

    mint T;
    {
        int t;
        cin >> t;
        T = t;
    }

    mint nu = 1;
    for(int i = 0; i <= n; ++i){
        nu *= (T - mint(i));
    }

    vector<mint> de(n+1, 1);
    for(int i = 1; i <= n; ++i){
        de[i] = de[i-1]*mint(i);
    }

    mint ans = 0;
    for(int i = 0; i <= n; ++i){
        mint temp = (nu / (T-mint(i))) / (de[i] * de[n-i]);
        if((n-i) % 2 == 1) temp = mint(0) - temp; // negate
        ans += temp * f[i];
    }
    cout << ans << "\n";

    return 0;
}
