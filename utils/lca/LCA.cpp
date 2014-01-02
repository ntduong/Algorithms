/**
    <O(nlogn), O(logn)> solution to Lowest Common Ancestor (LCA),
    where O(nlogn) is preprocessing time complexity, and O(logn) is for query time
    See also Topcoder Algorithm Tutorial on RMQ and LCA for more details.
    (c) Duong Nguyen
*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cassert>
#include<cstring>

using namespace std;

const int MAXN = 100;
const int MAXLOGN = 7;

// Number of nodes
int n;

// Adjacency list as tree DS
vector<int> G[MAXN+1];

// a[i][j] := 2^j-th ancestor of i
int a[MAXN+1][MAXLOGN+1];

// p[i] := parent of i; p[root] = -1
int p[MAXN+1];

// lv[i] := level of i, starting with root at level 0
// Initialize all to -1, also used to check if visited a node.
int lv[MAXN+1];

void dfs(int v, int level, int par){
    p[v] = par;
    lv[v] = level;
    for(auto nv : G[v]){
        if(lv[nv] == -1){
            dfs(nv, level+1, v);
        }
    }
}

// Precompute ancestor array a
void pre_compute(){
    memset(a, -1, sizeof(a));

    // Base case
    for(int i = 0; i < n; i++){
        a[i][0] = p[i];
    }

    for(int j = 1; (1 << j) < n; j++){
        for(int i = 0; i < n; i++){
            if(a[i][j-1] != -1) a[i][j] = a[a[i][j-1]][j-1];
        }
    }
}

// Find LCA of two nodes u, v
int query(int u, int v){

    if(lv[u] < lv[v]){ // guarantee lv[u] >= lv[v]
        swap(u, v);
    }

    int log; // [log(lv[u])]
    for(log = 0; (1 << log) <= lv[u]; log++);
    log--;

    // sanity check
    assert((1 << log) <= lv[u] && (1 << (log+1) > lv[u]));

    for(int i = log; i >= 0; i--){
        if(lv[u] - (1 << i) >= lv[v]){
            u = a[u][i];
        }
    }

    if(u == v) return u;

    // At this state, u and v should be in the same level
    assert(lv[u] == lv[v]);

    for(int i = log; i >= 0; i--){
        if(a[u][i] != -1 && a[u][i] != a[v][i]){
            u = a[u][i], v = a[v][i];
        }
    }

    assert(p[u] == p[v]);
    return p[u];
}


int main(){
    freopen("in.txt", "r", stdin);
    int E;
    cin >> n >> E;
    assert(E == n-1);
    for(int i = 1; i <= E; ++i){
        int from, to;
        cin >> from >> to;
        G[from].push_back(to);
        G[to].push_back(from);
    }

    int root = 0;
    memset(lv, -1, sizeof(lv));
    memset(p, 0, sizeof(p));

    dfs(root, 0, 0);

//#define TEST_DFS
#ifdef TEST_DFS
    for(int i = 0;  i < n; ++i) {
        cout << "Node #" << i+1 << ": level " << lv[i] << ", parent " << p[i]+1 << '\n';
    }
#endif

    pre_compute();

    // Query time
    int n_query;
    cin >> n_query;
    for(int i = 1; i <= n_query; i++){
        int u, v;
        cin >> u >> v;
        cout << "LCA(" << u << ", " << v << ") = " << query(u,v) << '\n';
    }

    return 0;
}
