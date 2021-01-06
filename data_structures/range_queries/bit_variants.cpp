// Fenwick Tree variants supporting:
// 1. Range update, Point query
// 2. Range query, Range update
// 3. Polynomial update (https://cses.fi/problemset/task/1736/)
// on an input array of size n in O(log n) time.

#include <iostream>
#include <vector>
#include <functional>

using namespace std;
using ll = long long;

template <typename T>
using FnType = function<void(T &, const T &)>;

template <typename T>
struct RangeUpdatePointQuery
{
  int n;
  T id;
  FnType<T> comb;
  vector<T> tree;

  void init(int sz, const T &ID, FnType<T> fn)
  {
    n = sz;
    id = ID;
    comb = fn;
    tree.assign(n + 1, id);
  }

  // Returns the current value of a[i]. i is 1-based index.
  T query(int i)
  {
    T ans = id;
    while (i > 0)
    {
      // Pro tip: Think about how to combine values of non-overlapping intervals to produce the final answer for your specific problems.
      comb(ans, tree[i]);

      i -= (i & -i);
    }
    return ans;
  }

  // a[i] += v for all i in [l..r], inclusively.
  // l and r are both 1-based indices.
  // O(logn).
  void range_update(int l, int r, const T &v)
  {
    point_update(l, v);
    point_update(r + 1, -v);
  }

  // Updates all intervals (to which a[i] contributes) about the change at a[i]. Clever use of this point update is key to support range update.
  void point_update(int i, T v)
  {
    while (i <= n)
    {
      comb(tree[i], v);
      i += (i & -i);
    }
  }
};

template <typename T>
struct RangeUpdateRangeQuery
{
  int n;
  RangeUpdatePointQuery<T> bit1, bit2;

  void init(int sz)
  {
    n = sz;
    bit1.init(n);
    bit2.init(n);
  }

  // a[i] += v for all i in [l..r] inclusively.
  // l and r are both 1-based indices.
  // O(logn).
  //
  // Think about sum[1..i] for different i
  // - 1 <= i < L, sum[1..i] should not be affected by the update to [l..r]. delta = 0 = 0*i  - v*0
  // - L <= i <= R, sum[1..i] += (i-L+1)*v. delta = (i-L+1)*v = v*i - (v*(L-1))
  // - i > R, sum[1..i] += (R-L+1)*v. delta = (R-L+1)*v = 0*i - (v*(L-1) - v*R)
  // Note delta = p1 * i - p2. The above observation gives rise to the idea of using two RangeUpdatePointQuery trees:
  // - tree 1 manages p1
  // - tree 2 manages p2
  void update(int l, int r, T v)
  {
    bit1.range_update(l, r, v);
    bit2.point_update(l, v * (l - 1));
    bit2.point_update(r + 1, -v * r);
  }

  // Return sum(a[1..i]).
  // i is 1-based index.
  // O(logn).
  T query(int i)
  {
    return bit1.query(i) * i - bit2.query(i);
  }
};

// Test for RangeUpdatePointQuery:
// - https://cses.fi/problemset/task/1651
// - Range increase, point query.
void testRangeUpdatePointQuery()
{
  int n, q;
  cin >> n >> q;
  RangeUpdatePointQuery<ll> ds;
  ds.init(n, /*id*/ 0, /*combine_fn*/ [](ll &a, const ll &b) {
    a += b;
  });
  for (int i = 1; i <= n; ++i)
  {
    int v;
    cin >> v;
    ds.range_update(i, i, v);
  }

  for (int i = 1; i <= q; ++i)
  {
    int t;
    cin >> t;
    if (t == 1)
    {
      // a[from..to] += u
      int from, to, u;
      cin >> from >> to >> u;
      ds.range_update(from, to, u);
    }
    else
    {
      // query a[k]
      int k;
      cin >> k;
      cout << ds.query(k) << '\n';
    }
  }
}

// https://cses.fi/problemset/task/1736
template <typename T>
struct PolynomialQueries
{
  RangeUpdatePointQuery<T> bit1, bit2, bit3;
  vector<T> prefix_sum;

  void init(const vector<T> &a, const T &id, function<void(T &, const T &)> comb)
  {
    int n = a.size();
    bit1.init(n, id, comb);
    bit2.init(n, id, comb);
    bit3.init(n, id, comb);
    prefix_sum.assign(n + 1, id);
    for (int i = 0; i < n; ++i)
    {
      prefix_sum[i + 1] += prefix_sum[i] + a[i];
    }
  }

  // [L,R]
  void update(int L, int R)
  {
    // coef for i^2
    bit1.point_update(L, 1);
    bit1.point_update(R + 1, -1);

    // coef for i
    bit2.point_update(L, 2 * L - 3);
    bit2.point_update(R + 1, -2 * L + 3);

    // coef for i^0
    bit3.point_update(L, (T)(L - 1) * (L - 2));
    bit3.point_update(R + 1, (T)(R) * (R - 2 * L + 3));
  }

  // [1..i]
  T query(int i)
  {
    return prefix_sum[i] + ((bit1.query(i) * i - bit2.query(i)) * i + bit3.query(i)) / 2;
  }

  // [L..R]
  T range_query(int L, int R)
  {
    if (L == 1)
    {
      return query(R);
    }
    return query(R) - query(L - 1);
  }
};

void testPolynomialQueries()
{
  PolynomialQueries<ll> ds;
  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  for (int i = 0; i < n; ++i)
  {
    cin >> a[i];
  }
  ds.init(a, 0, [](ll &x, const ll &y) { x += y; });

  for (int i = 1; i <= q; ++i)
  {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 1)
    {
      ds.update(x, y);
    }
    else
    {
      cout << ds.range_query(x, y) << '\n';
    }
  }
}

int main()
{
  testPolynomialQueries();
  return 0;
}