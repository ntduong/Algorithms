// Basic Binary Indexed Tree (aka, Fenwick Tree), supporting following operations on a sized-n array a in O(log n) time per op, and O(n) space:
// - Prefix range query: f(a[1..i]), such as sum(a[1..i])
// - Point update: u(a[i], v), such as a[i] += v
#include <iostream>
#include <vector>
#include <functional>

using namespace std;
using ll = long long;

// Returns the floor(log2(n)), the largest integer x such that 2^x <= n < 2^{x+1}.
// It's guaranteed that n >= 1.
int floorLog2(int n)
{
    // A hacky impl:
    // return sizeof(int) * 8 - __builtin_clz(n) - 1;

    int ans = 0;
    while ((1 << (ans + 1)) <= n)
    {
        ++ans;
    }
    return ans;
}

template <typename T>
using FnType = function<void(T &, const T &)>;

template <typename T>
struct BIT
{
    // Size of the array managed by BIT.
    int n;
    vector<T> tree;
    FnType<T> comb;
    T ZERO;

    void init(int sz, FnType<T> comb_fn, const T &zero)
    {
        n = sz;
        comb = comb_fn;
        ZERO = zero;
        tree.assign(n + 1, ZERO);
    }

    // a[i] += v, i is 1-based index.
    // O(log n)
    void update(int i, T v)
    {
        while (i <= n)
        {
            // Pro Tip: This is the place when you should adapt the logic for specific problems at hand. The key question to ask yourself here is: When the value of a[i] changes, how are we going to update all the intervals covering i?
            comb(tree[i], v);

            i += (i & -i);
        }
    }

    // prefixQuery on a[1..i], such as sum(a[1..i]) or (a[1] xor ... xor a[i]).
    T prefixQuery(int i)
    {
        T sum = ZERO;
        while (i)
        {
            // Pro Tip: This is the place when you should adapt the logic for specific problems at hand. The key question to ask yourself here is: how to combine values from all relevant *non-overlapping* intervals I1,..Ik, where I1 U I2 U ... Ik = [1..i].
            comb(sum, tree[i]);

            i -= i & -i;
        }
        return sum;
    }

    // Below are additional operations which only work in some specific cases such as sum.

    // Returns a[i]. i is 1-based index.
    // O(log n) (can be O(1) if we store a[1..n]).
    T get(int i) const
    {
        T ans = tree[i];
        int lo = i - (i & -i);
        i--;
        while (i > lo)
        {
            ans -= tree[i];
            i -= (i & -i);
        }
        return ans;
    }

    // Finds the first index i (1-based) where the prefixQuery(i) >= v.
    // O(logn): Only works for non-negative array a[1..n] with + op.
    // Alternative O(logn*logn) solution is straightforward using binary search with prefixQuery.
    int prefixSumSearch(T v)
    {
        int pos = 0;
        T sum = ZERO;

        // Maybe simpler to just replace floorLog2(n) with a large enough constant, e.g., 64 as the number of bits.
        for (int i = floorLog2(n); i >= 0; --i)
        {
            int new_pos = pos + (1 << i);
            if (new_pos > n)
            {
                continue;
            }
            if (sum + tree[new_pos] >= v)
            {
                continue;
            }

            pos = new_pos;
            sum += tree[new_pos];
        }

        // At the end of the above for-loop, pos is the last index that summing up to pos is still smaller than the target v. Thus pos+1 is the first index when prefix sum >= v.
        return pos + 1;
    }
};

// Test with https://atcoder.jp/contests/abc185/tasks/abc185_f
void test()
{
    int n, q;
    cin >> n >> q;

    BIT<ll> bit;
    bit.init(/*sz*/ n, /*comb_fn*/ [](ll &x, const ll &y) { x ^= y; }, /*zero*/ 0);

    for (int i = 0; i < n; ++i)
    {
        ll a;
        cin >> a;
        // 0 ^ a[i] = a[i]
        bit.update(i + 1, a);
    }
    for (int qq = 1; qq <= q; ++qq)
    {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1)
        {
            // a[x] ^= y
            bit.update(x, y);
        }
        else
        {
            // Compute xor(a[x..y])
            if (x == 1)
            {
                cout << bit.prefixQuery(y);
            }
            else
            {
                cout << (bit.prefixQuery(y) ^ bit.prefixQuery(x - 1));
            }
            cout << endl;
        }
    }
}

int main()
{
    test();
    return 0;
}
