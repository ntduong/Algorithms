/*
Range Minimum Query for 1D array using sparse table technique.
RMQ can be handled by other more complex DS such as segment tree, but sparse table is easier to implement and query is really fast (O(1)).

Ref:
- https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/Static%20Range%20Queries%20(9.1)/RMQ%20(9.1).h
- https://usaco.guide/PAPS.pdf#page=208
*/
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

using namespace std;

using ll = long long;

// Return maximum n such that 2^n <= x < 2^(n+1).
// Assume 1 byte = 8 bits (arch dependent)
// Not to condone this implementation though.
int log2(int x)
{
    return sizeof(int) * 8 - __builtin_clz(x) - 1;
}

// O(logx)
int log2_safe(int x)
{
    int n = 0;
    while (1 << (n + 1) <= x)
    {
        ++n;
    }
    return n;
}

// Sparse Table for RMQ-like queries on static array.
template <typename T>
struct SparseTable
{
    vector<T> v;
    vector<vector<T>> tb;
    function<T(const T &, const T &)> comb;

    // O(nlogn)
    void build(const vector<T> &inp, function<T(const T &, const T &)> comb_fn)
    {
        v = inp;
        comb = comb_fn;
        // Initially, add the first row to the table. tb[0][i] -> [i, i+2^0) = [i,i+1), which contains i only!
        tb = {vector<T>(inp)};
        for (int j = 1; (1 << j) <= v.size(); ++j)
        {
            tb.push_back(vector<T>(v.size() - (1 << j) + 1));
            for (int i = 0; i < tb[j].size(); ++i)
            {
                // combine [i, i+2^(j-1)) U [i+2^(j-1), i+2^j) -> [i, i+2^j)
                tb[j][i] = comb(tb[j - 1][i], tb[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    // O(1) query over [L,R) for idempotent ops, like min, max.
    // L and R are both 0-based indices.
    // For non-idempotent ops, use the O(logn) query below.
    T query(int L, int R)
    {
        int jmp = log2_safe(R - L);     // 2^jmp <= R-L
        T lo = tb[jmp][L];              // [L..L+2^jmp)
        T hi = tb[jmp][R - (1 << jmp)]; // [R-2^jmp..R)
        return comb(lo, hi);
    }

    // L and R are 0-based indices.
    T queryForNonIdempotent(int L, int R, const T &id)
    {
        T ans = id;
        int len = R - L;
        // [L,R) = [L,L+len)
        // Consider binary expansion: len = 2^k1+2^k2+...
        int index = -1;
        for (int i = tb.size(); i >= 0; --i)
        {
            if (len & (1 << i))
            {
                ans = comb(ans, tb[i][L]);
                L += (1 << i);
            }
        }
        return ans;
    }
};

// https://cses.fi/problemset/task/1647
// Range minimum query.
// O((n+q)logn)
void test1()
{
    int n, q;
    cin >> n >> q;
    SparseTable<int> st;
    vector<int> x(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> x[i];
    }
    st.build(x, [](const int &a, const int &b) -> int { return min(a, b); });
    for (int i = 1; i <= q; ++i)
    {
        int a, b;
        cin >> a >> b;
        cout << st.query(a - 1, b) << '\n';
    }
}

// https://cses.fi/problemset/task/1646
// Range sum query.
// O((n+q)logn)
void test2()
{
    int n, q;
    cin >> n >> q;
    vector<ll> x(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> x[i];
    }

    SparseTable<ll> st;
    // O(nlogn)
    st.build(x, [](const ll &a, const ll &b) -> ll { return a + b; });
    // O(qlogn)
    for (int i = 1; i <= q; ++i)
    {
        int a, b;
        cin >> a >> b;
        // O(logn)
        cout << st.queryForNonIdempotent(a - 1, b, 0) << '\n';
    }
}

// https://cses.fi/problemset/task/1650
// Range xor query.
// O((n+q)logn).
void test3()
{
    int n, q;
    cin >> n >> q;
    vector<ll> x(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> x[i];
    }

    SparseTable<ll> st;
    // O(nlogn)
    st.build(x, [](const ll &a, const ll &b) -> ll { return a ^ b; });
    // O(qlogn)
    for (int i = 1; i <= q; ++i)
    {
        int a, b;
        cin >> a >> b;
        // O(logn)
        cout << st.queryForNonIdempotent(a - 1, b, 0) << '\n';
    }
}

int main()
{
    //test1();
    //test2();
    test3();

    return 0;
}
