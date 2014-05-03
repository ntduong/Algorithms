/**
    Given a binary tree, remove the minimum number of nodes to make it a full binary tree.
    Source: GCJ 2014 R1A. Accepted solution.
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>
using namespace std;

const int MAXN = 1000;

int sz[MAXN+1]; // sz[v] := size of subtree rooted at v, including v

/**
    Compute the size of a subtree rooted at v.
    @param v: root node
    @param p: v's parent
    @param G: tree ds

    Note: Recursion + Memoization
*/
int get_subtree_size(int v, int p, const vector<vector<int>>& G){

    if(sz[v] != -1) return sz[v];
    int ans = 1;
    for(int i = 0; i < G[v].size(); ++i){
        if(G[v][i] != p){
            ans += get_subtree_size(G[v][i], v, G);
        }
    }
    return (sz[v] = ans);
}

/**
    Compute the minimum number of nodes to remove
    to make a tree rooted at r a full binary tree.
*/
int solve_helper(int r, int p, const vector<vector<int>>& G){

    // only one node
    if(G[r].size() == 0) return 0;

    // leaf node with only link to its parent (!= -1, not root)
    if(G[r].size() == 1 && p != -1) return 0;

    if((G[r].size() == 2 && p != -1) || (G[r].size() == 1)) {
        int ans = numeric_limits<int>::min();
        for(int i = 0; i < G[r].size(); ++i){
            if(G[r][i] != p){
                ans = get_subtree_size(G[r][i], r, G);
            }
        }
        return ans;
    }

    int ans = 0;
    pair<int,int> max_st(0,0);
    for(int i = 0; i < G[r].size(); ++i){
        if(G[r][i] != p){
            int s = get_subtree_size(G[r][i], r, G);
            ans += s;
            int cur = s-solve_helper(G[r][i], r, G);
            if(cur > max_st.first){
                max_st.second = max_st.first;
                max_st.first = cur;
            } else if(cur > max_st.second){
                max_st.second = cur;
            }
        }
    }

    return ans - max_st.first - max_st.second;
}

// Problem solver!
int solve(const vector<vector<int>>& G){

    int n = G.size();
    int ans = numeric_limits<int>::max();
    for(int i = 0; i < n; ++i){ // try i as root
        fill(sz, sz+n, -1);
        ans = min(ans, solve_helper(i, -1, G));
    }
    return ans;
}

int main(){

#ifdef CONTEST
    freopen("B-large-practice.in", "r", stdin);
    freopen("B-large.out", "w", stdout);
#endif

    // Speed up IO
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T, n;
    cin >> T;

    for(int t = 1; t <= T; ++t){
        cin >> n;
        auto G = vector<vector<int>>(n, vector<int>());
        for(int i = 1; i <= n-1; ++i){
            int x, y;
            cin >> x >> y;
            --x, --y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        cout << "Case #" << t << ": " << solve(G);
        if(t < T) cout << "\n";
    }

    return 0;
}
