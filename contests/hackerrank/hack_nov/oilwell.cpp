#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cassert>

using namespace std;
typedef pair<int,int> ii;

const int MAXN = 55;
// input board
int b[MAXN][MAXN];
// d[i][j] := ACME distance between oil wells i, j
int d[MAXN*MAXN][MAXN*MAXN];
// cost[i] := the currently maximum ACME distance between oil well i and existing oil wells
int cost[MAXN*MAXN];
// visited[i] := whether oil well i was visited or not
bool visited[MAXN*MAXN];

/**
    Start from oil well wi and greedily moving.
*/
int go(const vector<ii>& W, int wi){
    int nw = static_cast<int> (W.size());

    // initialize, or reset cost and visited arrays
    for(int i = 0; i < nw; i++){
        cost[i] = -1;
        visited[i] = false;
    }

    visited[wi] = true;
    cost[wi] = 0;
    int cur_id = wi;

    int ret = 0; // return value

    for(int iter = 1; iter <= nw-1; iter++){
        int select_id = -1;
        int min_cost = 105;
        for(int i = 0; i < nw; i++){
            if(visited[i]) continue;
            // update cost[i]
            cost[i] = max(cost[i], d[cur_id][i]);

            if(min_cost > cost[i]){
                min_cost = cost[i];
                select_id = i;
            }
        }
        ret += min_cost;
        cur_id = select_id;
        visited[select_id] = true;
    }

    // check if all oil wells visited
    for(int i = 0; i < nw; i++){
        assert(visited[i] == true);
    }

    return ret;
}

int main(){
    freopen("test.txt", "r", stdin);
    int R, C;
    cin >> R >> C;
    vector<ii> W;
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            cin >> b[i][j];
            if(b[i][j] == 1) {
                W.push_back(make_pair(i,j));
            }
        }
    }

    int nw = static_cast<int> (W.size());
    for(int i = 0; i < nw; i++){
        for(int j = i+1; j < nw; j++){
            int r1 = W[i].first;
            int c1 = W[i].second;
            int r2 = W[j].first;
            int c2 = W[j].second;
            d[i][j] = d[j][i] = max(abs(r1-r2), abs(c1-c2));
        }
    }

    int ans = go(W, 0);
    for(int i = 1; i < nw; i++){
        ans = min(ans, go(W, i));
    }

    cout << ans << endl;
    return 0;
}
