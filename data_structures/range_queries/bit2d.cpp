// 2D Fenwich tree, supporting update and query on 2D grid of size H * W in O(log H * log W) time:
// - update: grid[r][c] += v
// - query: sum(grid[r1..r2][c1..c2]), r1 <= r2, c1 <= c2

#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
using BIT2D = vector<vector<int>>;

// a[r][c] += v
void update(BIT2D &bit, int r, int c, int v)
{
  int n = bit.size() - 1;
  for (int i = r; i <= n; i += (i & -i))
  {
    for (int j = c; j <= n; j += (j & -j))
    {
      bit[i][j] += v;
    }
  }
}

// sum(a[0..r][0..c])
int query(const BIT2D &bit, int r, int c)
{
  int ans = 0;
  for (int i = r; i > 0; i -= (i & -i))
  {
    for (int j = c; j > 0; j -= (j & -j))
    {
      ans += bit[i][j];
    }
  }
  return ans;
}

// sum(a[r1..r2][c1..c2])
int range_query(const BIT2D &bit, int r1, int c1, int r2, int c2)
{
  // r1 <= r2, c1 <= c2
  int ans = query(bit, r2, c2);
  ans -= query(bit, r2, c1 - 1);
  ans -= query(bit, r1 - 1, c2);
  ans += query(bit, r1 - 1, c1 - 1);

  return ans;
}

// https://cses.fi/problemset/task/1739
void test()
{
  int n, q;
  cin >> n >> q;
  BIT2D bit2d(n + 1, vector<int>(n + 1, 0));
  for (int i = 0; i < n; ++i)
  {
    string s;
    cin >> s;
    for (int j = 0; j < n; ++j)
    {
      if (s[j] == '*')
      {
        update(bit2d, i + 1, j + 1, 1);
      }
    }
  }

  for (int i = 1; i <= q; ++i)
  {
    int t;
    cin >> t;
    if (t == 2)
    {
      int y1, x1, y2, x2;
      cin >> y1 >> x1 >> y2 >> x2;
      cout << range_query(bit2d, y1, x1, y2, x2) << endl;
    }
    else
    {
      int y, x;
      cin >> y >> x;
      int cur_val = range_query(bit2d, y, x, y, x);
      if (cur_val == 1)
      {
        // 1 - 1 = 0
        update(bit2d, y, x, -1);
      }
      else
      {
        // 0 + 1 = 1
        update(bit2d, y, x, 1);
      }
    }
  }
}

int main()
{
  test();
  return 0;
}