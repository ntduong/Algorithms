// Convex Hull Trick (CHT): A technique for speeding up DP update.
// In a nutshell, the most basic CHT is a data structure maintaining
// a set of lines, i.e., functions of form f(x) = ax + b. It supports
// the following operations efficiently:
// 1. add a new line f(x) = ax+b
// 2. query(x) returns the min (or max) f(x) over all existing fs
// Under the constraints that lines are added in the order of
// non-increasing slopes (a1 >= a2 >= ...) and queries are asked
// in the order of non-decreasing points (x1 <= x2 <= ...),
// CHT can handle N additions and Q queries in O(N+Q) *amortized* time.
// See e.g., https://www.slideshare.net/hcpc_hokudai/convex-hull-trick for a good tutorial.

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

using ll = long long;

const ll INF = 1e13;

template <typename T>
struct F
{
    // Represent f(x) = ax+b
    T a, b;
    F(T a, T b) : a(a), b(b) {}
    T eval(T x)
    {
        return a * x + b;
    }
};

// Assume the following simple setup:
// - Fs are added in the order of non-increasing slopes, i.e., a1 >= a2 >= ...
// - Query points are in non-decreasing order, i.e., x1 <= x2 <= ...
// Under this assumption, the total time for N additions and Q queries are O(N+Q).
template <typename T>
struct Manager
{
    deque<F<T>> fs;

    // (Maybe) Adds f to the set of functions, and returns true if f is added.
    // Returning false means f is not added as it's not needed by the min query.
    // The invariant to maintain after each add operation is that the slopes of functions in the set are __strictly__ decreasing.
    bool add(const F<T> &f)
    {
        if (fs.empty())
        {
            fs.push_back(f);
            return true;
        }

        int sz = fs.size();
        if (sz == 1)
        {
            if (fs[0].a != f.a)
            {
                fs.push_back(f);
                return true;
            }
            else
            {
                // f1 and f are parallel, so if f.b < f1.b, we replace f1 with f since we're interested in min query.
                if (fs[0].b > f.b)
                {
                    fs.pop_front();
                    fs.push_back(f);
                    return true;
                }
                return false;
            }
        }
        while (true)
        {
            int sz = fs.size();
            if (sz < 2)
            {
                // we know that f.a is strictly smaller than the existing f if any.
                fs.push_back(f);
                return true;
            }

            // sz >= 2
            if (shouldRemoveF2(fs[sz - 2], fs[sz - 1], f))
            {
                fs.pop_back();
            }
            else
            {
                fs.push_back(f);
                return true;
            }
        }
    }

    // Returns true if adding f3 to {f1, f2} makes f2 no longer be minimum for any query and thus f2 should be removed (to reduce computation cost). Note that f1.a > f2.a >= f3.a and let x_{ij} be the x-coordinate of the intersection of f_i and f_j, then the condition is x_12 >= x_13.
    bool shouldRemoveF2(const F<T> &f1, const F<T> &f2, const F<T> &f3)
    {
        // x_12 = (b2-b1)/(a1-a2) >= (b3-b1)/(a1-a3) = x_13
        return (f2.b - f1.b) * (f1.a - f3.a) >= (f3.b - f1.b) * (f1.a - f2.a);
    }

    // Query min f_i(x) over all f_i in the set fs.
    // Assume fs is not empty. It's the caller's responsibility to verify that before calling.
    T get_min(T x)
    {
        while (fs.size() >= 2 && fs[0].eval(x) >= fs[1].eval(x))
        {
            fs.pop_front();
        }
        return fs.front().eval(x);
    }

    bool empty() const
    {
        return fs.empty();
    }
};

int main()
{
    // Test with Atcoder DP contest's Problem Z (Frog 3)
    // https://atcoder.jp/contests/dp/tasks/dp_z
    int n;
    ll c;
    cin >> n >> c;
    vector<ll> h(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> h[i];

    // dp[i] := min cost of jumping from 1 to i. The answer is dp[n]
    // dp[i] := min{dp[j] + (hi-hj)^2+C} for 1 <= j < i.
    // => dp[i] = min{-2hj * hi + dp[j]+hj^2} + hi^2 + C.
    // Naively computing the min results in O(n^2) solution, but for a big n (>=1e5), we could use Convex Hull Trick optimization technique (implemented in the Manager struct) to efficiently compute the min and obtain O(n) solution in this case.
    vector<ll> dp(n + 1, INF);
    dp[1] = 0;
    Manager<ll> cht;
    cht.add({-2 * h[1], dp[1] + h[1] * h[1]});
    for (int i = 2; i <= n; ++i)
    {
        dp[i] = min(dp[i], cht.get_min(h[i]) + h[i] * h[i] + c);
        // Add for the next iteration (i+1)
        cht.add({-2 * h[i], dp[i] + h[i] * h[i]});
    }

    cout << dp[n] << endl;

    return 0;
}