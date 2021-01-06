#include <iostream>
#include <vector>
#include <cmath>
#include <numeric> // for iota
#include <functional>

using namespace std;

using ll = long long;

template <typename T>
using FnType = function<T(const T &, const T &)>;

// Block decomposition of an input array.
template <typename T>
struct BlockDC
{
  // input array
  vector<T> a;
  vector<T> blocks;
  // block size
  int bsz;
  T id;
  FnType<T> comb_fn;

  void init(const vector<T> &inp, int _bsz, const T &_id, FnType<T> _comb_fn)
  {
    a = inp;
    id = _id;
    bsz = _bsz;
    comb_fn = _comb_fn;

    int n_blocks = (inp.size() + bsz - 1) / bsz;
    blocks.assign(n_blocks, id);
  }

  void build()
  {
    for (int i = 0; i < a.size(); ++i)
    {
      blocks[i / bsz] = comb_fn(blocks[i / bsz], a[i]);
    }
  }

  // range query [L, R). L and R are 0-based indices.
  T query(int L, int R)
  {
    T ans = id;
    while ((L < R) && (L % bsz != 0))
    {
      ans = comb_fn(ans, a[L]);
      ++L;
    }
    while (L + bsz <= R)
    {
      ans = comb_fn(ans, blocks[L / bsz]);
      L += bsz;
    }
    while (L < R)
    {
      --R;
      ans = comb_fn(ans, a[R]);
    }

    return ans;
  }

  // a[i] = v. i is 0-based index.
  // O(1). Update may not be feasible for some comb_fn.
  void update(int i, T v)
  {
    // As an example, implement update when comb_fn is sum.
    blocks[i / bsz] -= a[i];
    a[i] = v;
    blocks[i / bsz] += a[i];
  }
};

// https://cses.fi/problemset/result/1456795/
// Range XOR query with square root decomposition on O((Q+N) sqrt(N)).
void test1()
{
  int n, q;
  cin >> n >> q;

  vector<ll> x(n);
  for (int i = 0; i < n; ++i)
  {
    cin >> x[i];
  }

  BlockDC<ll> dc;
  dc.init(x, /*blocksize*/ sqrt(n), /*id*/ 0, [](const ll &a, const ll &b) -> ll {
    return a ^ b;
  });

  dc.build();
  for (int i = 1; i <= q; ++i)
  {
    int a, b;
    cin >> a >> b;
    cout << dc.query(a - 1, b) << endl;
  }
}

int main()
{
  test1();
  return 0;
}