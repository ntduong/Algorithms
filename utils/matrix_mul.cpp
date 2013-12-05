/**
    Matrix multiplicaton and pow
    (c) Duong Nguyen
*/
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long ll;
typedef vector<int> vec;
typedef vector<vec> mat;

const int MOD = 1000000007;

mat mod_mul(mat& A, mat& B){
    int nr = static_cast<int>(A.size());
    int nc = static_cast<int>(B[0].size());
    int nk = static_cast<int>(A[0].size());

    mat D(nr, vec(nc));
    for(int r = 0; r < nr; ++r){
        for(int c = 0; c < nc; ++c){
            for(int k = 0; k < nk; ++k){
                D[r][c] = (D[r][c] + (A[r][k]*B[k][c] % MOD)) % MOD;
            }
        }
    }
    return D;
}

/**
    Compute A^n
    Time complexity: O(m^3 * logn)
*/
mat mod_pow(mat A, ll n){
    int m = static_cast<int>(A.size());
    mat unit(m, vec(m));
    for(int i = 0; i < m; ++i) unit[i][i] = 1;
    if(n == 0) return unit;
    if(n == 1) return A;
    mat B(m, vec(m));
    B = mod_pow(mod_mul(A, A), n/2);
    if(n & 1) B = mod_mul(B, A);
    return B;
}

mat iter_mod_pow(mat A, ll n){
    if(n == 0) return A;
    int m = static_cast<int>(A.size());
    mat B(m, vec(m));
    for(int i = 0; i < m; ++i) B[i][i] = 1;
    while(n > 0){
        if(n & 1) B = mod_mul(B, A);
        A = mod_mul(A, A);
        n >>= 1;
    }
    return B;
}

void show(mat A){
    int nr = static_cast<int> (A.size());
    int nc = static_cast<int> (A[0].size());
    for(int i = 0; i < nr; ++i){
        for(int j = 0; j < nc; ++j){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << "====\n";
}

int main(){
    mat A(2, vec(2));
    A[0][0] = 1, A[0][1] = 1, A[1][0] = 1, A[1][1] = 0;
    mat A3 = mod_pow(A, 3);
    mat A3_2 = iter_mod_pow(A, 3);
    mat t = mod_mul(A, A);
    mat A3_3 = mod_mul(t, A);
    show(A3);
    show(A3_2);
    show(A3_3);

    return 0;
}
