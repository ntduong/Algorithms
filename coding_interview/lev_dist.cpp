#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define MAX_N 100
#define DEBUG 1
#define RIGHT 1
#define DOWN 2
#define DIAG 3

int dp[MAX_N+1][MAX_N+1];
int p[MAX_N+1][MAX_N+1];

// Levenstein distance between u and v using DP: u -> v
// u --> vertical, v --> horizontal
int lev_dist(const string &u, const string &v){
    int lenu = (int)u.length();
    int lenv = (int)v.length();
    for(int i = 0; i <= lenu; i++) dp[i][0] = i;
    for(int i = 0; i <= lenv; i++) dp[0][i] = i;
    for(int i = 1; i <= lenu; i++){
        for(int j = 1; j <= lenv; j++){
            int delta = ((u[i-1] != v[j-1]) ? 1 : 0);//buggy: u[i-1],v[j-1] not u[i],v[j]
            dp[i][j] = dp[i][j-1]+1;
            p[i][j] = RIGHT;
            if(dp[i][j] > dp[i-1][j]+1){
                dp[i][j] = dp[i-1][j]+1;
                p[i][j] = DOWN;
            }
            if(dp[i][j] > dp[i-1][j-1] + delta){
                dp[i][j] = dp[i-1][j-1] + delta;
                p[i][j] = DIAG;
                if(delta){
                    // check if replace
                }
            }

            //dp[i][j] = min(min(dp[i][j-1]+1, dp[i-1][j]+1), dp[i-1][j-1]+delta);
        }
    }
    #ifdef DEBUG
    for(int i = 0; i <= lenu; i++){
        for(int j = 0; j <= lenv; j++){
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;

    for(int i = 0; i <= lenu; i++){
        for(int j = 0; j <= lenv; j++){
            cout << p[i][j] << " ";
        }
        cout << endl;
    }
    #endif

    return dp[lenu][lenv];
}

int main(){
    string s1 = "01101101";
    string s2 = "0101010";
    cout << lev_dist(s1, s2) << endl;
    return 0;
}
