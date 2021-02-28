#include <iostream>

using namespace std;

using ll = long long;

// O(log max(a,b))
template <typename T>
T gcd(T a, T b) {
  if (b == 0) {
    return a;
  }
  return gcd<T>(b, a % b);
}

// Finds gcd(a,b) and x, y s.t. ax + by = gcd(a,b).
template <typename T>
T ext_gcd(T a, T b, T &x, T &y) {
  T d = a;
  if (b != 0) {
    d = ext_gcd<T>(b, a % b, y, x);
    y -= (a / b) * x;
  } else {
    // b = 0 then gcd(a,b) = a = a*1 + b*0
    x = 1;
    y = 0;
  }

  return d;
}

// Finds x s.t. ax = 1 (mod m) given (a,m)=1.
// (a,m)=1=ax+my.
template <typename T>
T mod_inverse(T a, T m) {
  T x, y;
  ext_gcd<T>(a, m, x, y);
  return (m + x % m) % m;
}

// Computes C(n,k) % m.
template <typename T>
T comb(T n, T k, T m) {
  if (n < k || k < 0 || n < 0) return 0;
  T ret = 1;
  for (T i = 0; i < k; ++i) {
    ret = ret * (n - i) % m;
    ret = ret * mod_inverse<T>(i + 1, m) % m;
  }

  return ret;
}

// Solves for x in ax = b (mod m). The solution when exists is of the form x
// (mod n). Returns false if no solution exists, in which case x and n are
// undefined.
template <typename T = int>
bool solve_lineq(T a, T b, T m, T &x, T &n) {
  T d = gcd<T>(a, m);
  if (b % d != 0) {
    return false;
  }

  // ax - b = tm -> a/d x - b/d = t m/d -> a' x = b' (mod m') with (a',m') = 1.
  // The solution is x = inverse(a') b' (mod m').
  a /= d;
  b /= d;
  m /= d;
  x = mod_inverse(a, m) * b % m;
  n = m;

  return true;
}

// Solves a linear system: A_i x = B_i (mod M_i) for i=1,...n (n >= 1).
// Returns a pair (b, m) means x=b(mod m) is the solution. The pair (0, -1)
// means no solution existed.
template <typename T = int>
pair<T, T> solve_linsys(const vector<T> &A, const vector<T> &B,
                        const vector<T> &M) {
  // Consider the first equation x = 0 (mod 1).
  T x = 0, m = 1;

  for (int i = 0; i < A.size(); ++i) {
    // x (mod m) (1) -> x+tm -> substitute into (2) below
    // A[i] x = B[i] (mod M[i]) (2)
    // -> (A[i]*m) * t = (B[i]-A[i]*x) (mod M[i]) (3)
    T a = A[i] * m;
    T b = B[i] - A[i] * x;
    T t, n;
    // solve (3) for solution t (mod n) if existed.
    bool has_sol = solve_lineq<T>(a, b, M[i], t, n);
    if (!has_sol) {
      return make_pair(0, -1);
    }
    // substitute back into (1): x = old_x + m (t+kn) = old_x + mt + k*nm =
    // old_x + mt (mod mn)
    x = x + m * t;
    m *= n;
  }
  return make_pair((x + m) % m, m);
}

int main() {
  // solve 2x = 3 (mod 5)
  int x, n;
  bool has_sol = solve_lineq(2, 3, 5, x, n);
  if (has_sol) {
    cout << x << " mod " << n << endl;
  } else {
    cout << "No solution!" << endl;
  }

  return 0;
}