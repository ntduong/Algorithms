#include <iostream>
#include <vector>
#include <functional>

using namespace std;

using ll = long long;

// Non-recursive basic Segment Tree, supporting range query and point update in O(logn) where n is the size of the input array.
// Implementation details:
// - use 0-based index for the input array
// - use 1-based index for the tree nodes, i.e., the root node is at index 1.
// - use half-closed range, i.e., [L,R)
template <typename T>
struct SegTree
{
    int n;
    T id;
    function<T(const T &, const T &)> comb;
    vector<T> tree;

    void init(int sz, const T &ID, function<T(const T &, const T &)> comb_fn)
    {
        n = sz;
        id = ID;
        comb = comb_fn;
        tree.assign(2 * n, id);
    }

    void _pull(int p)
    {
        // tree[p] = comb(tree[2*p], tree[2*p+1])
        tree[p] = comb(tree[p << 1], tree[(p << 1) | 1]);
    }

    // Set a[p] = val. Note p is 0-based index.
    void update(int p, T val)
    {
        // p + n is the leaf node corresponding to a[p].
        p += n;
        tree[p] = val;
        for (p /= 2; p; p /= 2)
        {
            _pull(p);
        }
    }

    // Range query a[L, R)
    T query(int L, int R)
    {
        T res = id;
        for (L += n, R += n; L < R; L /= 2, R /= 2)
        {
            // If L is odd -> L is the right child of its parent, so its parent should be excluded; otherwise the left child (i.e., left sibling of L) would also included in the range, which is incorrect.
            if (L & 1)
            {
                // res = comb(res, tree[L]) then L += 1
                // So that L /= 2 is the node right next to the original L's parent.
                res = comb(res, tree[L++]);
            }
            // Think about maintaining the invariant that R is always one-position to the right of the included range.
            if (R & 1)
            {
                res = comb(tree[--R], res);
            }
        }
        return res;
    }
};

// https://cses.fi/problemset/task/1649
// Min range query, point update.
void test1()
{
    int n, q;
    cin >> n >> q;
    SegTree<int> segTree;
    segTree.init(n, /*id=*/1e9, [](const int &a, const int &b) -> int {
        return min(a, b);
    });
    for (int i = 0; i < n; ++i)
    {
        int v;
        cin >> v;
        segTree.update(i, v);
    }

    for (int i = 1; i <= q; ++i)
    {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1)
        {
            // a[x] = y
            // x-1 for 0-based index
            segTree.update(x - 1, y);
        }
        else
        {
            // min(a[x..y])
            cout << segTree.query(x - 1, y) << '\n';
        }
    }
}

// https://cses.fi/problemset/task/1648
// Range sum query, point update.
void test2()
{
    int n, q;
    cin >> n >> q;
    SegTree<ll> segTree;
    segTree.init(n, /*id=*/0, [](const ll &a, const ll &b) -> ll {
        return a + b;
    });
    for (int i = 0; i < n; ++i)
    {
        int v;
        cin >> v;
        segTree.update(i, v);
    }

    for (int i = 1; i <= q; ++i)
    {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1)
        {
            // a[x] = y
            // x-1 for 0-based index
            segTree.update(x - 1, y);
        }
        else
        {
            // min(a[x..y])
            cout << segTree.query(x - 1, y) << '\n';
        }
    }
}

int main()
{
    test2();
    return 0;
}